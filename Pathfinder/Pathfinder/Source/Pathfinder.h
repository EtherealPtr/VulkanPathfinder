#pragma once

#include "Tile.h"
#include <list>
#include <memory>

class Pathfinder
{
public:
	Pathfinder();

	void DisplayPathAnimated(const double _dt, const float _animSpeed = 0.5f);
	const std::vector<std::vector<std::shared_ptr<Tile>>>& GetGrid() const { return m_Grid; }

private:
	void FindPath();
	void CreateGrid();
	void AssignNeighbors();
	void MarkAsProcessed(Tile* _tile);
	void CreatePath(Tile* _tile);
	void DisplayPath();
	uint32_t CalculateDistance(Tile* _currentTile, Tile* _nextTile);

private:
	uint32_t m_TotalRows;
	uint32_t m_TotalCols;
	bool m_AllowDiagonals;
	std::vector<std::vector<std::shared_ptr<Tile>>> m_Grid;
	std::shared_ptr<Tile> m_Start;
	std::shared_ptr<Tile> m_Goal;
	std::list<Tile*> m_OpenList;
	std::list<Tile*> m_ClosedList;

	// Debug
	std::vector<Tile*> PathTiles;
	double currentTime{ 0.0 };
};
