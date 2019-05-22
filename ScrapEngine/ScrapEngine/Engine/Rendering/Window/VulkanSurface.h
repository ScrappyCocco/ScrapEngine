#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <Engine/Rendering/Window/GameWindow.h>
#include <Engine/Rendering/Instance/VukanInstance.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanSurface
		{
		private:
			/**
			 * \brief represents an abstract type of surface to present rendered images to.
			 */
			vk::SurfaceKHR surface_;

			static VulkanSurface* instance_;

			VulkanSurface() = default;
		public:
			void init(ScrapEngine::Render::GameWindow* window_ref);

			~VulkanSurface();

			static VulkanSurface* get_instance();

			void create_surface(ScrapEngine::Render::GameWindow* window_ref);

			vk::SurfaceKHR* get_surface();
		};
	}
}
