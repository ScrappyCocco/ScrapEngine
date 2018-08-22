#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "../Queue/GraphicsQueue.h"

namespace ScrapEngine {

	class VulkanSwapChain
	{
	private:
		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;

		VkDevice deviceRef;
		VkSurfaceKHR surfaceRef;
	public:
		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		VulkanSwapChain(SwapChainSupportDetails swapChainSupport, GraphicsQueue::QueueFamilyIndices indices, VkDevice input_deviceRef, VkSurfaceKHR input_surfaceRef, uint32_t WIDTH, uint32_t HEIGHT);
		~VulkanSwapChain();

		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);

		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, uint32_t WIDTH, uint32_t HEIGHT);

		VkSwapchainKHR getSwapChain() const;

		const std::vector<VkImage>* getSwapChainImagesVector();
		VkFormat getSwapChainImageFormat() const;
		VkExtent2D getSwapChainExtent() const;
	};

}

