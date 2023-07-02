#include "Entity.h"
#include <vulkan/vulkan.h>
#include <glm/gtx/transform.hpp>

Entity::Entity(const PrimitiveShape _primitiveShape) : 
	m_Transform{},
	m_Shape(_primitiveShape),
	m_Color(glm::vec3(1.0f, 0.0f, 1.0f))
{}

Entity::~Entity()
{}

void Entity::Draw(const VkCommandBuffer& _cmdBuffer, const uint32_t _numOfIndices) const
{
	vkCmdDrawIndexed(_cmdBuffer, _numOfIndices, 1, 0, 0, 0);
}
