#include "UniformBuffer.h"
#include "../../../Debug/DebugLog.h"
#include "../BaseBuffer.h"
#include <glm/gtc/matrix_transform.hpp>

ScrapEngine::UniformBuffer::UniformBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, const std::vector<vk::Image>* swapChainImages, vk::Extent2D input_swapChainExtent) 
	: deviceRef(input_deviceRef), swapChainExtent(input_swapChainExtent)
{
	vk::DeviceSize bufferSize(sizeof(UniformBufferObject));

	swapChainImagesSize = swapChainImages->size();
	uniformBuffers.resize(swapChainImagesSize);
	uniformBuffersMemory.resize(swapChainImagesSize);

	for (size_t i = 0; i < swapChainImagesSize; i++) {
		BaseBuffer::createBuffer(deviceRef, PhysicalDevice, &bufferSize, vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, uniformBuffers[i], uniformBuffersMemory[i]);
	}
	//Map memory
	mappedMemory.resize(swapChainImagesSize);
	for (size_t i = 0; i < swapChainImagesSize; i++) {
		deviceRef->mapMemory(uniformBuffersMemory[i], 0, sizeof(UniformBufferObject), vk::MemoryMapFlags(), &mappedMemory[i]);
	}
}

ScrapEngine::UniformBuffer::~UniformBuffer()
{
	for (size_t i = 0; i < swapChainImagesSize; i++) {
		deviceRef->destroyBuffer(uniformBuffers[i]);
		deviceRef->unmapMemory(uniformBuffersMemory[i]);
		deviceRef->freeMemory(uniformBuffersMemory[i]);
	}
}

void ScrapEngine::UniformBuffer::updateUniformBuffer(uint32_t currentImage, ScrapEngine::Transform object_transform, ScrapEngine::Camera* RenderCamera)
{
	glm::mat4 view = glm::lookAt(RenderCamera->getCameraLocation(), RenderCamera->getCameraLocation() + RenderCamera->getCameraFront(), RenderCamera->getCameraUp());;

	UniformBufferObject ubo = {};
	ubo.model = glm::translate(glm::mat4(1.0f), object_transform.location);
	ubo.model = glm::scale(ubo.model, object_transform.scale);
	if (object_transform.rotation.x != 0 || object_transform.rotation.y != 0 || object_transform.rotation.z != 0) {
		ubo.model = glm::rotate(ubo.model, glm::radians(90.0f), object_transform.rotation);
	}
	ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, RenderCamera->getCameraMinDrawDistance(), RenderCamera->getCameraMaxDrawDistance());
	ubo.view = view;
	ubo.proj[1][1] *= -1;
	
	/*void* data;
	deviceRef->mapMemory(uniformBuffersMemory[currentImage], 0, sizeof(ubo), vk::MemoryMapFlags(), &data);
	vkMapMemory(*deviceRef, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(*deviceRef, uniformBuffersMemory[currentImage]);
	deviceRef->unmapMemory(uniformBuffersMemory[currentImage]);*/
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

