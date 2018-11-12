#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../Queue/GraphicsQueue.h"

namespace ScrapEngine {

	class VulkanSwapChain
	{
	private:
		vk::SwapchainKHR swapChain;
		std::vector<vk::Image> swapChainImages;
		vk::Format swapChainImageFormat;
		vk::Extent2D swapChainExtent;

		vk::SurfaceKHR* surfaceRef;
	public:
		struct SwapChainSupportDetails {
			vk::SurfaceCapabilitiesKHR capabilities;
			std::vector<vk::SurfaceFormatKHR> formats;
			std::vector<vk::PresentModeKHR> presentModes;
		};

		VulkanSwapChain(SwapChainSupportDetails swapChainSupport, GraphicsQueue::QueueFamilyIndices indices, vk::SurfaceKHR* input_surfaceRef, const uint32_t& WIDTH, const uint32_t& HEIGHT, bool vsync);
		~VulkanSwapChain();

		vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);

		vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR> availablePresentModes, bool vsync);

		vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const uint32_t& WIDTH, const uint32_t& HEIGHT);

		vk::SwapchainKHR getSwapChain() const;

		const std::vector<vk::Image>* getSwapChainImagesVector();
		vk::Format getSwapChainImageFormat() const;
		vk::Extent2D getSwapChainExtent() const;
	};

}

