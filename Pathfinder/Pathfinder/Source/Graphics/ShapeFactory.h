#pragma once

#include "PrimitiveShape.h"
#include "Vertex.h"
#include <vector>
#include <cstdint>

class ShapeFactory
{
public:
	static void GetVertices(const PrimitiveShape _shape, std::vector<Vertex>& _vertices, std::vector<uint16_t>& _indices);
	static uint16_t GetIndicesCount(const PrimitiveShape _shape);
};
