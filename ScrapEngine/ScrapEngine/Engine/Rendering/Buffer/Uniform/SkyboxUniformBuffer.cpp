#include "SkyboxUniformBuffer.h"
#include "../../../Debug/DebugLog.h"
#include "../BaseBuffer.h"
#include <glm/gtc/matrix_transform.hpp>

ScrapEngine::SkyboxUniformBuffer::SkyboxUniformBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, const std::vector<vk::Image>* swapChainImages, vk::Extent2D input_swapChainExtent)
	: deviceRef(input_deviceRef), swapChainExtent(input_swapChainExtent)
{
	vk::DeviceSize bufferSize(sizeof(SkyboxUniformBufferObject));

	swapChainImagesSize = swapChainImages->size();
	uniformBuffers.resize(swapChainImagesSize);
	uniformBuffersMemory.resize(swapChainImagesSize);

	for (size_t i = 0; i < swapChainImagesSize; i++) {
		BaseBuffer::createBuffer(deviceRef, PhysicalDevice, &bufferSize, vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, uniformBuffers[i], uniformBuffersMemory[i]);
	}
	//Map memory
	mappedMemory.resize(swapChainImagesSize);
	for (size_t i = 0; i < swapChainImagesSize; i++) {
		deviceRef->mapMemory(uniformBuffersMemory[i], 0, sizeof(SkyboxUniformBufferObject), vk::MemoryMapFlags(), &mappedMemory[i]);
	}
}

ScrapEngine::SkyboxUniformBuffer::~SkyboxUniformBuffer()
{
	for (size_t i = 0; i < swapChainImagesSize; i++) {
		deviceRef->destroyBuffer(uniformBuffers[i]);
		deviceRef->unmapMemory(uniformBuffersMemory[i]);
		deviceRef->freeMemory(uniformBuffersMemory[i]);
	}
}

void ScrapEngine::SkyboxUniformBuffer::updateUniformBuffer(uint32_t currentImage, ScrapEngine::Transform object_transform, ScrapEngine::Camera* RenderCamera)
{
	SkyboxUniformBufferObject uboVS = {};

	glm::vec3 rotation = { -7.25f, -120.0f, 0.0f };
	// Skybox
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	uboVS.projection = glm::perspective(glm::radians(60.0f), (float)swapChainExtent.width / (float)swapChainExtent.height, 0.001f, 256.0f);

	uboVS.model = glm::mat4(1.0f);
	uboVS.model = viewMatrix * glm::translate(uboVS.model, glm::vec3(0, 0, 0));
	uboVS.model = glm::rotate(uboVS.model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	uboVS.model = glm::rotate(uboVS.model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	uboVS.model = glm::rotate(uboVS.model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	/*void* data;
	vkMapMemory(*deviceRef, uniformBuffersMemory[currentImage], 0, sizeof(uboVS), 0, &data);
	memcpy(data, &uboVS, sizeof(uboVS));
	vkUnmapMemory(*deviceRef, uniformBuffersMemory[currentImage]);*/
	memcpy(mappedMemory[currentImage], &uboVS, sizeof(uboVS));
}

const std::vector<vk::Buffer>* ScrapEngine::SkyboxUniformBuffer::getUniformBuffers()
{
	return &uniformBuffers;
}

const std::vector<vk::DeviceMemory>* ScrapEngine::SkyboxUniformBuffer::getUniformBuffersMemory()
{
	return &uniformBuffersMemory;
}

