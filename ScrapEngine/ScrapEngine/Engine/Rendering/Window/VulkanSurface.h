#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "GameWindow.h"
#include "../Instance/VukanInstance.h"

namespace ScrapEngine {

	class VulkanSurface
	{
	private:
		VkSurfaceKHR surface; //represents an abstract type of surface to present rendered images to.
		VkInstance instanceRef; //Reference to vulkan instance
	public:
		VulkanSurface(ScrapEngine::VukanInstance* input_instanceRef, ScrapEngine::GameWindow* windowRef);
		~VulkanSurface();

		void createSurface(ScrapEngine::GameWindow* windowRef);

		VkSurfaceKHR getSurface() const;
	};

}

