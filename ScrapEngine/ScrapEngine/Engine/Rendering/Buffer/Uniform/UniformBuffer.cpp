#include "UniformBuffer.h"

#include "../BaseBuffer.h"
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>

ScrapEngine::UniformBuffer::UniformBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, const std::vector<VkImage>* swapChainImages)
	: deviceRef(input_deviceRef)
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	swapChainImagesSize = swapChainImages->size();
	uniformBuffers.resize(swapChainImagesSize);
	uniformBuffersMemory.resize(swapChainImagesSize);

	for (size_t i = 0; i < swapChainImagesSize; i++) {
		BaseBuffer::createBuffer(deviceRef, PhysicalDevice, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
	}
}

ScrapEngine::UniformBuffer::~UniformBuffer()
{
	for (size_t i = 0; i < swapChainImagesSize; i++) {
		vkDestroyBuffer(deviceRef, uniformBuffers[i], nullptr);
		vkFreeMemory(deviceRef, uniformBuffersMemory[i], nullptr);
	}
}

void ScrapEngine::UniformBuffer::updateUniformBuffer(uint32_t currentImage, VkExtent2D* swapChainExtent)
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	UniformBufferObject ubo = {};
	ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent->width / (float)swapChainExtent->height, 0.1f, 10.0f);
	ubo.proj[1][1] *= -1;

	void* data;
	vkMapMemory(deviceRef, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(deviceRef, uniformBuffersMemory[currentImage]);
}

const std::vector<VkBuffer>* ScrapEngine::UniformBuffer::getUniformBuffers()
{
	return &uniformBuffers;
}

const std::vector<VkDeviceMemory>* ScrapEngine::UniformBuffer::getUniformBuffersMemory()
{
	return &uniformBuffersMemory;
}

