#include "VulkanSemaphoresManager.h"

#include <stdexcept>

ScrapEngine::VulkanSemaphoresManager::VulkanSemaphoresManager(vk::Device* input_deviceRef, unsigned short int INPUT_MAX_FRAMES_IN_FLIGHT)
	: deviceRef(input_deviceRef), MAX_FRAMES_IN_FLIGHT(INPUT_MAX_FRAMES_IN_FLIGHT)
{
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

	vk::SemaphoreCreateInfo semaphoreInfo;

	vk::FenceCreateInfo fenceInfo(vk::FenceCreateFlagBits::eSignaled);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (deviceRef->createSemaphore(&semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != vk::Result::eSuccess ||
			deviceRef->createSemaphore(&semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != vk::Result::eSuccess ||
			deviceRef->createFence(&fenceInfo, nullptr, &inFlightFences[i]) != vk::Result::eSuccess) {
			throw std::runtime_error("Failed to create VulkanSemaphoresManager for a frame!");
		}
	}
}

ScrapEngine::VulkanSemaphoresManager::~VulkanSemaphoresManager()
{
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		deviceRef->destroySemaphore(renderFinishedSemaphores[i]);
		deviceRef->destroySemaphore(imageAvailableSemaphores[i]);
		deviceRef->destroyFence(inFlightFences[i]);
	}
}

int ScrapEngine::VulkanSemaphoresManager::getMaxFramesInFlight() const
{
	return MAX_FRAMES_IN_FLIGHT;
}

const std::vector<vk::Semaphore>* ScrapEngine::VulkanSemaphoresManager::getImageAvailableSemaphoresVector()
{
	return &imageAvailableSemaphores;
}

const std::vector<vk::Semaphore>* ScrapEngine::VulkanSemaphoresManager::getRenderFinishedSemaphoresVector()
{
	return &renderFinishedSemaphores;
}

const std::vector<vk::Fence>* ScrapEngine::VulkanSemaphoresManager::getInFlightFencesVector()
{
	return &inFlightFences;
}
