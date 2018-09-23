#pragma once

#include <vulkan/vulkan.hpp>
#include "../VulkanCommandBuffer.h"

#include <stb_image.h>

namespace ScrapEngine {

	class StagingBuffer
	{
	private:
		vk::Buffer stagingBuffer;
		vk::DeviceMemory stagingBufferMemory;

		vk::Device* deviceRef;
	public:
		StagingBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, vk::DeviceSize* imageSize, stbi_uc* pixels);

		template <class T> 
		StagingBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, vk::DeviceSize* bufferSize, const std::vector<T>* vectorData);

		~StagingBuffer();

		static void copyBufferToImage(vk::Device* input_deviceRef, vk::Buffer* buffer, vk::Image* image, uint32_t width, uint32_t height, vk::CommandPool* commandPool, vk::Queue* graphicsQueue);
		vk::Buffer* getStagingBuffer();
		vk::DeviceMemory* getStagingBufferMemory();

	};
	template<class T>
	inline StagingBuffer::StagingBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, vk::DeviceSize* bufferSize, const std::vector<T>* vectorData)
		: deviceRef(input_deviceRef)
	{
		BaseBuffer::createBuffer(input_deviceRef, PhysicalDevice, bufferSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, stagingBuffer, stagingBufferMemory);
		void* data;
		deviceRef->mapMemory(stagingBufferMemory, 0, *bufferSize, vk::MemoryMapFlags(), &data);
		memcpy(data, vectorData->data(), static_cast<size_t>(*bufferSize));
		deviceRef->unmapMemory(stagingBufferMemory);
	}
}

