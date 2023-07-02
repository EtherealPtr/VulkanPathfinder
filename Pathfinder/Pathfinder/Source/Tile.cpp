#include "Tile.h"

Tile::Tile(const uint32_t _gridX, const uint32_t _gridY) :
	Entity(PrimitiveShape::Square),
	m_GridIndexX(_gridX),
	m_GridIndexY(_gridY),
	m_GCost(UINT32_MAX),
	m_HCost(UINT32_MAX),
	m_Parent(nullptr),
	m_Neighbors{},
	m_Traversable(true)
{
	m_Transform.SetScale(glm::vec3(66.0f, 60.0f, 1.0f));
	SetTraversable(m_Traversable);
}

void Tile::SetTraversable(const bool _traversable)
{
	m_Traversable = _traversable;

	if (!m_Traversable)
	{
		SetSolidColor(glm::vec3(0.5f, 0.0f, 0.0f));
	}
	else
	{
		SetSolidColor(glm::vec3(0.0f));
	}
}

void Tile::SetNeightbor(Tile* _tile)
{
	m_Neighbors.push_back(_tile);
}
