#include "UniformBuffer.h"
#include "../../../Debug/DebugLog.h"
#include "../BaseBuffer.h"
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

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
}

ScrapEngine::UniformBuffer::~UniformBuffer()
{
	for (size_t i = 0; i < swapChainImagesSize; i++) {
		deviceRef->destroyBuffer(uniformBuffers[i]);
		deviceRef->freeMemory(uniformBuffersMemory[i]);
	}
}

void ScrapEngine::UniformBuffer::updateUniformBuffer(uint32_t currentImage, ScrapEngine::Transform object_transform, ScrapEngine::Camera* RenderCamera)
{

	glm::mat4 view = glm::lookAt(RenderCamera->getCameraTransform().location, RenderCamera->getCameraTransform().location * RenderCamera->getCameraFront(), RenderCamera->getCameraUp());;

	UniformBufferObject ubo = {};
	ubo.model = glm::translate(glm::mat4(1.0f), object_transform.location);
	ubo.model = glm::scale(ubo.model, object_transform.scale);
	if (object_transform.rotation.x != 0 || object_transform.rotation.y != 0 || object_transform.rotation.z != 0) {
		ubo.model = glm::rotate(ubo.model, glm::radians(90.0f), object_transform.rotation);
	}
	ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, RenderCamera->getCameraMinDrawDistance(), RenderCamera->getCameraMaxDrawDistance());
	ubo.view = view;
	ubo.proj[1][1] *= -1;
	

	void* data;
	vkMapMemory(*deviceRef, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(*deviceRef, uniformBuffersMemory[currentImage]);
}

const std::vector<vk::Buffer>* ScrapEngine::UniformBuffer::getUniformBuffers()
{
	return &uniformBuffers;
}

const std::vector<vk::DeviceMemory>* ScrapEngine::UniformBuffer::getUniformBuffersMemory()
{
	return &uniformBuffersMemory;
}

