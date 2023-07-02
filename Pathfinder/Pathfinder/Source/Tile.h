#pragma once

#include "Entity.h"
#include <vector>

class Tile : public Entity
{
public:
	Tile(const uint32_t _gridX = 0, const uint32_t _gridY = 0);

	void SetGCost(const uint32_t _gCost) { m_GCost = _gCost; }
	void SetHCost(const uint32_t _hCost) { m_HCost = _hCost; }
	void SetParent(Tile* _parentTile) { m_Parent = _parentTile; }
	void SetTraversable(const bool _traversable);
	void SetNeightbor(Tile* _tile);

	const std::vector<Tile*>& GetNeighbors() { return m_Neighbors; }
	bool GetTraversable() const { return m_Traversable; }
	Tile* GetParent() const { return m_Parent; }
	uint32_t GetGCost() const { return m_GCost; }
	uint32_t GetHCost() const { return m_HCost; }
	uint32_t GetFCost() const { return (m_GCost + m_HCost); }
	uint32_t GetGridX() const { return m_GridIndexX; }
	uint32_t GetGridY() const { return m_GridIndexY; }

private:
	uint32_t m_GridIndexX;
	uint32_t m_GridIndexY;
	uint32_t m_GCost;
	uint32_t m_HCost;
	Tile* m_Parent;
	std::vector<Tile*> m_Neighbors;
	bool m_Traversable;
};
