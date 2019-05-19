#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "GameWindow.h"
#include "../Instance/VukanInstance.h"

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanSurface
		{
		private:
			vk::SurfaceKHR surface_; //represents an abstract type of surface to present rendered images to.
		public:
			static const vk::SurfaceKHR* static_surface_ref;

			VulkanSurface(ScrapEngine::Render::GameWindow* window_ref);
			~VulkanSurface();

			void create_surface(ScrapEngine::Render::GameWindow* window_ref);

			vk::SurfaceKHR* get_surface();
		};
	}
}
