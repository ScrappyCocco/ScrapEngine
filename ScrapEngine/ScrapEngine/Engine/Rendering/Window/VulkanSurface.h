#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "GameWindow.h"
#include "../Instance/VukanInstance.h"

namespace ScrapEngine {

	class VulkanSurface
	{
	private:
		vk::SurfaceKHR surface; //represents an abstract type of surface to present rendered images to.
	public:
		static const vk::SurfaceKHR* StaticSurfaceRef;

		VulkanSurface(ScrapEngine::GameWindow* windowRef);
		~VulkanSurface();

		void createSurface(ScrapEngine::GameWindow* windowRef);

		vk::SurfaceKHR* getSurface();
	};

}

