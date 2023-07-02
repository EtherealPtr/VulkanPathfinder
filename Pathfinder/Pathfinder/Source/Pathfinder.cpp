#include "Pathfinder.h"
#include <cmath>
#include <chrono>

Pathfinder::Pathfinder() : 
	m_TotalRows(12),
	m_TotalCols(18),
	m_AllowDiagonals(true)
{
	CreateGrid();

	m_Start = m_Grid[2][2];
	m_Goal = m_Grid[2][6];

	m_Grid[1][5]->SetTraversable(false);
	m_Grid[2][5]->SetTraversable(false);
	m_Grid[3][5]->SetTraversable(false);
	m_Grid[4][5]->SetTraversable(false);

	m_Start->SetSolidColor(glm::vec3(0.0f, 1.0f, 0.0f));
	m_Goal->SetSolidColor(glm::vec3(0.0f, 0.0f, 1.0f));

	m_OpenList.push_back(m_Start.get());

	FindPath();
}

void Pathfinder::CreateGrid()
{
	const float startX = 30.0f;
	const float startY = 30.0f;
	const float tileSpacing = 1.0f;

	m_Grid.resize(m_TotalRows);
	for (uint32_t i = 0; i < m_TotalRows; ++i)
	{
		m_Grid[i].resize(m_TotalCols);
	}

	for (uint32_t i = 0; i < m_TotalRows; ++i)
	{
		for (uint32_t j = 0; j < m_TotalCols; ++j)
		{
			m_Grid[i][j] = std::make_shared<Tile>(i, j);

			const glm::vec3 tileSize = m_Grid[i][j]->m_Transform.GetScale();
			const float xPos = startX + (j * (tileSize.x + tileSpacing));
			const float yPos = startY + (i * (tileSize.y + tileSpacing));

			m_Grid[i][j]->m_Transform.SetPosition(glm::vec3(xPos, yPos, -1.0f));
		}
	}

	AssignNeighbors();
}

void Pathfinder::AssignNeighbors()
{
	for (uint32_t i = 0; i < m_TotalRows; ++i)
	{
		for (uint32_t j = 0; j < m_TotalCols; ++j)
		{
			Tile* currentTile = m_Grid[i][j].get();

			if (i > 0) currentTile->SetNeightbor(m_Grid[i - 1][j].get());												// Top tile
			if (j < m_TotalCols - 1) currentTile->SetNeightbor(m_Grid[i][j + 1].get());									// Right tile
			if (i < m_TotalRows - 1) currentTile->SetNeightbor(m_Grid[i + 1][j].get());									// Bottom tile
			if (j > 0) currentTile->SetNeightbor(m_Grid[i][j - 1].get());												// Left tile
		
			if (!m_AllowDiagonals)
			{
				continue;
			}

			if (i > 0 && j > 0) currentTile->SetNeightbor(m_Grid[i - 1][j - 1].get());									// Top-left tile
			if (i > 0 && j < m_TotalCols - 1) currentTile->SetNeightbor(m_Grid[i - 1][j + 1].get());					// Top-right tile
			if (i < m_TotalRows - 1 && j > 0) currentTile->SetNeightbor(m_Grid[i + 1][j - 1].get());					// Bottom-left tile
			if (i < m_TotalRows - 1 && j < m_TotalCols - 1) currentTile->SetNeightbor(m_Grid[i + 1][j + 1].get());		// Bottom-right tile
		}
	}
}

void Pathfinder::MarkAsProcessed(Tile* _tile)
{
	// Move _tile from m_OpenList to m_ClosedList
	const auto iter = std::find(m_OpenList.begin(), m_OpenList.end(), _tile);

	if (iter != m_OpenList.end())
	{
		m_OpenList.erase(iter);
		m_ClosedList.push_back(_tile);
	}
}

void Pathfinder::CreatePath(Tile* _tile)
{
	Tile* pathTile = _tile;
	while (pathTile->GetParent() != nullptr)
	{
		if (pathTile->GetParent() == m_Start.get())
		{
			return;
		}
	
		pathTile = pathTile->GetParent();
		PathTiles.emplace_back(pathTile);
	}
}

void Pathfinder::DisplayPath()
{
	for (Tile* pathTile : PathTiles)
	{
		pathTile->SetSolidColor(glm::vec3(0.0f, 1.0f, 0.0f));
	}
}

void Pathfinder::DisplayPathAnimated(const double _dt, const float _animSpeed)
{
	static size_t index = 0;

	currentTime += 1.0 * _dt;
	if (currentTime < _animSpeed)
	{
		return;
	}

	if (index < PathTiles.size())
	{
		++index;
		PathTiles[PathTiles.size() - index]->SetSolidColor(glm::vec3(0.0f, 1.0f, 0.0f));
		currentTime = 0.0;
	}
}

uint32_t Pathfinder::CalculateDistance(Tile* _currentTile, Tile* _nextTile)
{
	const uint32_t adjacentMoveCost = 10;
	const uint32_t diagonalMoveCost = 14;

	int32_t dx = std::abs(static_cast<int32_t>(_currentTile->GetGridX() - _nextTile->GetGridX()));
	int32_t dy = std::abs(static_cast<int32_t>(_currentTile->GetGridY() - _nextTile->GetGridY()));

	if (!m_AllowDiagonals)
	{
		// Use the standard Manhattan distance heuristic if diagonals are not allowed
		return adjacentMoveCost * (dx + dy);
	}
	
	// Otherwise, use a modified heuristic to take diagonals into consideration
	if (dx > dy)
	{
		return diagonalMoveCost * dy + adjacentMoveCost * (dx - dy);
	}

	return diagonalMoveCost * dx + adjacentMoveCost * (dy - dx);
}

void Pathfinder::FindPath()
{
	auto startTime = std::chrono::high_resolution_clock::now();

	while (!m_OpenList.empty())
	{
		Tile* currentTile = *m_OpenList.begin();

		for (Tile* tile : m_OpenList)
		{
			if (tile->GetFCost() < currentTile->GetFCost() || 
				tile->GetFCost() == currentTile->GetFCost() && tile->GetHCost() < currentTile->GetHCost())
			{
				currentTile = tile;
			}
		}

		MarkAsProcessed(currentTile);

		if (currentTile == m_Goal.get())
		{
			const auto endTime = std::chrono::high_resolution_clock::now();
			const auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
			printf("Found path at location <%d, %d> in %lld ms\n", currentTile->GetGridX(), currentTile->GetGridY(), timeTaken);
			CreatePath(currentTile);
			//DisplayPath();
			return;
		}

		for (Tile* neighborTile : currentTile->GetNeighbors())
		{
			if (!neighborTile->GetTraversable() || 
				std::find(m_ClosedList.begin(), m_ClosedList.end(), neighborTile) != m_ClosedList.end())
			{
				continue;
			}

			if (currentTile->GetGCost() == UINT32_MAX)
				currentTile->SetGCost(0);

			const uint32_t gCost = currentTile->GetGCost() + CalculateDistance(currentTile, neighborTile);

			if (gCost < neighborTile->GetGCost())
			{
				neighborTile->SetGCost(gCost);
				neighborTile->SetHCost(CalculateDistance(neighborTile, m_Goal.get()));
				neighborTile->SetParent(currentTile);

				const auto iter = std::find(m_OpenList.begin(), m_OpenList.end(), neighborTile);
				if (iter == m_OpenList.end())
				{
					m_OpenList.push_back(neighborTile);
				}
			}
		}
	}

	printf("Pathfinder failed to find a solution\n");
	return;
}
