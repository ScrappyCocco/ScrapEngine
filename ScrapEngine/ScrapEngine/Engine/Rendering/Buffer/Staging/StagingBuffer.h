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
	public:
		StagingBuffer(const vk::DeviceSize& imageSize, stbi_uc* pixels);

		template <class T> 
		StagingBuffer(const vk::DeviceSize& bufferSize, const std::vector<T>* vectorData);

		~StagingBuffer();

		static void copyBufferToImage(vk::Buffer* buffer, vk::Image* image, const uint32_t& width, const uint32_t& height);
		static void copyBufferToImage(vk::Buffer* buffer, vk::Image* image, const uint32_t& width, const uint32_t& height, vk::BufferImageCopy* region, int regioncount = 1, vk::ImageLayout layout = vk::ImageLayout::eTransferDstOptimal);


		vk::Buffer* getStagingBuffer();
		vk::DeviceMemory* getStagingBufferMemory();

	};
	template<class T>
	inline StagingBuffer::StagingBuffer(const vk::DeviceSize& bufferSize, const std::vector<T>* vectorData)
	{
		BaseBuffer::createBuffer(bufferSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, stagingBuffer, stagingBufferMemory);
		void* data;
		VulkanDevice::StaticLogicDeviceRef->mapMemory(stagingBufferMemory, 0, bufferSize, vk::MemoryMapFlags(), &data);
		memcpy(data, vectorData->data(), static_cast<size_t>(bufferSize));
		VulkanDevice::StaticLogicDeviceRef->unmapMemory(stagingBufferMemory);
	}
}

