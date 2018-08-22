#include "VertexBuffer.h"

#include "../../Memory/MemoryManager.h"
#include "../BaseBuffer.h"
#include "../Staging/StagingBuffer.h"

ScrapEngine::VertexBuffer::VertexBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, const std::vector<ScrapEngine::Vertex>* vertices, VkCommandPool commandPool, VkQueue graphicsQueue)
	: deviceRef(input_deviceRef)
{
	VkDeviceSize bufferSize = sizeof((*vertices)[0]) * vertices->size();


	StagingBuffer* Staging = new StagingBuffer(deviceRef, PhysicalDevice, bufferSize, vertices);

	BaseBuffer::createBuffer(deviceRef, PhysicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	BaseBuffer::copyBuffer(deviceRef, commandPool, graphicsQueue, Staging->getStagingBuffer(), vertexBuffer, bufferSize);

	delete Staging;
}

ScrapEngine::VertexBuffer::~VertexBuffer()
{
	vkDestroyBuffer(deviceRef, vertexBuffer, nullptr);
	vkFreeMemory(deviceRef, vertexBufferMemory, nullptr);
}

VkBuffer ScrapEngine::VertexBuffer::getVertexBuffer() const
{
	return vertexBuffer;
}
