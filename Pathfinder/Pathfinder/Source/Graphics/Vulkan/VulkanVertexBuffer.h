#pragma once

#include <cstdint>

typedef struct VkDevice_T* VkDevice;
typedef struct VkPhysicalDevice_T* VkPhysicalDevice;
typedef struct VkCommandBuffer_T* VkCommandBuffer;
typedef struct VkBuffer_T* VkBuffer;
typedef struct VkDeviceMemory_T* VkDeviceMemory;
typedef struct VkCommandPool_T* VkCommandPool;
typedef struct VkQueue_T* VkQueue;

class VulkanVertexBuffer
{
public:
	VulkanVertexBuffer(const VkDevice& _logicalDevice, const VkPhysicalDevice& _physicalDevice, const VkCommandPool& _commandPool, const VkQueue& _graphicsQueue, void* _vertexData, const uint64_t _sizeOfVertexData, void* _indexData, const uint64_t _sizeOfIndexData);
	~VulkanVertexBuffer();

	void Bind(const VkCommandBuffer& _commandBuffer);

private:
	void CreateVertexBuffer(void* _data, const uint64_t _size);
	void CreateIndexBuffer(void* _data, const uint64_t _size);
	void CleanUpVertexBuffer();
	void CleanUpIndexBuffer();

private:
	VkDevice m_LogicalDevice;
	VkPhysicalDevice m_PhysicalDevice;
	VkCommandPool m_CommandPool;
	VkQueue m_GraphicsQueue;
	VkBuffer m_VertexBuffer;
	VkBuffer m_IndexBuffer;
	VkDeviceMemory m_VertexBufferMemory;
	VkDeviceMemory m_IndexBufferMemory;
};