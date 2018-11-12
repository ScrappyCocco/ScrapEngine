#include "UniformBuffer.h"
#include "../../../Debug/DebugLog.h"
#include "../BaseBuffer.h"
#include <glm/gtc/matrix_transform.hpp>

ScrapEngine::UniformBuffer::UniformBuffer(const std::vector<vk::Image>* swapChainImages, const vk::Extent2D& input_swapChainExtent)
	: swapChainExtent(input_swapChainExtent)
{
	vk::DeviceSize bufferSize(sizeof(UniformBufferObject));

	swapChainImagesSize = swapChainImages->size();
	uniformBuffers.resize(swapChainImagesSize);
	uniformBuffersMemory.resize(swapChainImagesSize);

	for (size_t i = 0; i < swapChainImagesSize; i++) {
		BaseBuffer::createBuffer(bufferSize, vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, uniformBuffers[i], uniformBuffersMemory[i]);
	}
	//Map memory
	mappedMemory.resize(swapChainImagesSize);
	for (size_t i = 0; i < swapChainImagesSize; i++) {
		VulkanDevice::StaticLogicDeviceRef->mapMemory(uniformBuffersMemory[i], 0, sizeof(UniformBufferObject), vk::MemoryMapFlags(), &mappedMemory[i]);
	}
}

ScrapEngine::UniformBuffer::~UniformBuffer()
{
	for (size_t i = 0; i < swapChainImagesSize; i++) {
		VulkanDevice::StaticLogicDeviceRef->destroyBuffer(uniformBuffers[i]);
		VulkanDevice::StaticLogicDeviceRef->unmapMemory(uniformBuffersMemory[i]);
		VulkanDevice::StaticLogicDeviceRef->freeMemory(uniformBuffersMemory[i]);
	}
}

void ScrapEngine::UniformBuffer::updateUniformBuffer(const uint32_t& currentImage, const ScrapEngine::Transform& object_transform, ScrapEngine::Camera* RenderCamera)
{
	UniformBufferObject ubo = {};

	ubo.model = glm::translate(glm::mat4(1.0f), object_transform.location);
	ubo.model = glm::scale(ubo.model, object_transform.scale);
	if (object_transform.rotation.x != 0 || object_transform.rotation.y != 0 || object_transform.rotation.z != 0) {
		ubo.model = glm::rotate(ubo.model, glm::radians(90.0f), object_transform.rotation);
	}
	ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, RenderCamera->getCameraMinDrawDistance(), RenderCamera->getCameraMaxDrawDistance());
	ubo.view = glm::lookAt(RenderCamera->getCameraLocation(), RenderCamera->getCameraLocation() + RenderCamera->getCameraFront(), RenderCamera->getCameraUp());
	ubo.proj[1][1] *= -1; //Invert image for openGL style
	
	memcpy(mappedMemory[currentImage], &ubo, sizeof(ubo));
}

const std::vector<vk::Buffer>* ScrapEngine::UniformBuffer::getUniformBuffers()
{
	return &uniformBuffers;
}

const std::vector<vk::DeviceMemory>* ScrapEngine::UniformBuffer::getUniformBuffersMemory()
{
	return &uniformBuffersMemory;
}

