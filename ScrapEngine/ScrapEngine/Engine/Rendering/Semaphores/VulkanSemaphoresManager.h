#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace ScrapEngine {

	class VulkanSemaphoresManager
	{
	private:
		std::vector<vk::Semaphore> imageAvailableSemaphores;
		std::vector<vk::Semaphore> renderFinishedSemaphores;
		std::vector<vk::Fence> inFlightFences;

		const unsigned short int MAX_FRAMES_IN_FLIGHT = 2;
	public:
		VulkanSemaphoresManager(unsigned short int INPUT_MAX_FRAMES_IN_FLIGHT = 2);
		~VulkanSemaphoresManager();

		int getMaxFramesInFlight() const;

		const std::vector<vk::Semaphore>* getImageAvailableSemaphoresVector();
		const std::vector<vk::Semaphore>* getRenderFinishedSemaphoresVector();
		const std::vector<vk::Fence>* getInFlightFencesVector();
	};

}

