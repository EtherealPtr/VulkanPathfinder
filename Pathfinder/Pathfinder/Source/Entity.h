#pragma once

#include "Graphics/PrimitiveShape.h"
#include "Graphics/MVP.h"
#include "Transform.h"

typedef struct VkCommandBuffer_T* VkCommandBuffer;

class Entity
{
public:
	Entity(const PrimitiveShape _primitiveShape = PrimitiveShape::Empty);
	~Entity();

	void SetSolidColor(const glm::vec3& _col) { m_Color = _col; }
	void Draw(const VkCommandBuffer& _cmdBuffer, const uint32_t _numOfIndices) const;
	PrimitiveShape GetShape() const { return m_Shape; }
	const glm::vec3& GetColor() const { return m_Color; }

public:
	Transform m_Transform;

private:
	PrimitiveShape m_Shape;
	glm::vec3 m_Color;
};