#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace ScrapEngine {

	class VulkanSemaphoresManager
	{
	private:
		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;

		VkDevice deviceRef;

		const unsigned short int MAX_FRAMES_IN_FLIGHT = 2;
	public:
		VulkanSemaphoresManager(VkDevice input_deviceRef, unsigned short int INPUT_MAX_FRAMES_IN_FLIGHT = 2);
		~VulkanSemaphoresManager();

		int getMaxFramesInFlight() const;

		const std::vector<VkSemaphore>* getImageAvailableSemaphoresVector();
		const std::vector<VkSemaphore>* getRenderFinishedSemaphoresVector();
		const std::vector<VkFence>* getInFlightFencesVector();
	};

}

