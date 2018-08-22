#include "VulkanSemaphoresManager.h"

#include <stdexcept>

ScrapEngine::VulkanSemaphoresManager::VulkanSemaphoresManager(VkDevice input_deviceRef, unsigned short int INPUT_MAX_FRAMES_IN_FLIGHT)
	: deviceRef(input_deviceRef), MAX_FRAMES_IN_FLIGHT(INPUT_MAX_FRAMES_IN_FLIGHT)
{
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(deviceRef, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(deviceRef, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(deviceRef, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create VulkanSemaphoresManager for a frame!");
		}
	}
}

ScrapEngine::VulkanSemaphoresManager::~VulkanSemaphoresManager()
{
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(deviceRef, renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(deviceRef, imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(deviceRef, inFlightFences[i], nullptr);
	}
}

int ScrapEngine::VulkanSemaphoresManager::getMaxFramesInFlight() const
{
	return MAX_FRAMES_IN_FLIGHT;
}

const std::vector<VkSemaphore>* ScrapEngine::VulkanSemaphoresManager::getImageAvailableSemaphoresVector()
{
	return &imageAvailableSemaphores;
}

const std::vector<VkSemaphore>* ScrapEngine::VulkanSemaphoresManager::getRenderFinishedSemaphoresVector()
{
	return &renderFinishedSemaphores;
}

const std::vector<VkFence>* ScrapEngine::VulkanSemaphoresManager::getInFlightFencesVector()
{
	return &inFlightFences;
}
