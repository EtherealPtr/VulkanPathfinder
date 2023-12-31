#include "VulkanDescriptorPool.h"
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <array>

VulkanDescriptorPool::VulkanDescriptorPool(const VkDevice& _logicalDevice, const VkDescriptorSetLayout& _layout, const uint32_t _maxSets) :
	m_LogicalDevice(_logicalDevice),
	m_DescriptorSetLayout(_layout),
	m_DescriptorPool(VK_NULL_HANDLE)
{
	std::array<VkDescriptorPoolSize, 2> poolSizes{};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = 1;

	poolSizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
	poolSizes[1].descriptorCount = 1;

	VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{};
	descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	descriptorPoolCreateInfo.maxSets = _maxSets;
	descriptorPoolCreateInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	descriptorPoolCreateInfo.pPoolSizes = poolSizes.data();

	if (vkCreateDescriptorPool(_logicalDevice, &descriptorPoolCreateInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS)
	{
		throw std::runtime_error("ERROR: Failed to create a descriptor pool");
	}
}

VulkanDescriptorPool::~VulkanDescriptorPool()
{
	if (m_DescriptorPool == VK_NULL_HANDLE) 
		return;

	vkDestroyDescriptorPool(m_LogicalDevice, m_DescriptorPool, nullptr);
	m_DescriptorPool = VK_NULL_HANDLE;
}