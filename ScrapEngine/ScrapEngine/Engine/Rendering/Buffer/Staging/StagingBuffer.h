#pragma once

#include <vulkan/vulkan.h>
#include "../VulkanCommandBuffer.h"

#include <stb_image.h>

namespace ScrapEngine {

	class StagingBuffer
	{
	private:
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		VkDevice deviceRef;
	public:
		StagingBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, VkDeviceSize imageSize, stbi_uc* pixels);

		template <class T> 
		StagingBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, VkDeviceSize bufferSize, const std::vector<T>* vectorData);

		~StagingBuffer();

		static void copyBufferToImage(VkDevice input_deviceRef, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandPool commandPool, VkQueue graphicsQueue);
		VkBuffer getStagingBuffer() const;
		VkDeviceMemory getStagingBufferMemory() const;

	};
	template<class T>
	inline StagingBuffer::StagingBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, VkDeviceSize bufferSize, const std::vector<T>* vectorData)
		: deviceRef(input_deviceRef)
	{
		BaseBuffer::createBuffer(input_deviceRef, PhysicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
		void* data;
		vkMapMemory(deviceRef, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vectorData->data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(deviceRef, stagingBufferMemory);
	}
}

