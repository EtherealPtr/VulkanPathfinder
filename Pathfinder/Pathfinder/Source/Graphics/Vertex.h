#pragma once

#include "glm/glm.hpp"

struct Vertex
{
	Vertex(const float _pX = 0.0f, const float _pY = 0.0f, const float _pZ = 0.0f,
		   const float _r = 1.0f, const float _g = 1.0f, const float _b = 1.0f) :
		position(_pX, _pY, _pZ),
		color(_r, _g, _b)
	{}

	glm::vec3 position;
	glm::vec3 color;
};