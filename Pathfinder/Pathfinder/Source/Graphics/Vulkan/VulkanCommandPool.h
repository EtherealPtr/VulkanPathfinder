#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkCommandPool_T* VkCommandPool;

class VulkanCommandPool
{
public:
	VulkanCommandPool(const VkDevice& _logicalDevice, const unsigned int _queueFamilyIndex);
	~VulkanCommandPool();

	VkCommandPool Get() const { return m_CommandPool; }

private:
	VkDevice m_LogicalDevice;
	VkCommandPool m_CommandPool;
};