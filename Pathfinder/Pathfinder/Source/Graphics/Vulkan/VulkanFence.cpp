#include "VulkanFence.h"
#include <vulkan/vulkan.h>
#include <stdexcept>


VulkanFence::VulkanFence(const VkDevice& _logicalDevice, const uint16_t _count) :
	m_LogicalDevice(_logicalDevice),
	m_Fences{ VK_NULL_HANDLE }
{
	VkFenceCreateInfo fenceCreateInfo{};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	m_Fences.resize(_count);

	for (size_t i = 0; i < _count; ++i)
	{
		if (vkCreateFence(_logicalDevice, &fenceCreateInfo, nullptr, &m_Fences[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("ERROR: Failed to create fence\n");
		}
	}
}

VulkanFence::~VulkanFence()
{
	for (size_t i = 0; i < m_Fences.size(); ++i)
	{
		vkDestroyFence(m_LogicalDevice, m_Fences[i], nullptr);
		m_Fences[i] = VK_NULL_HANDLE;
	}
}

void VulkanFence::Wait(const uint16_t _fenceIndex) const
{
	vkWaitForFences(m_LogicalDevice, 1, &m_Fences[_fenceIndex], VK_TRUE, UINT64_MAX);
}

void VulkanFence::Reset(const uint16_t _fenceIndex) const
{
	vkResetFences(m_LogicalDevice, 1, &m_Fences[_fenceIndex]);
}