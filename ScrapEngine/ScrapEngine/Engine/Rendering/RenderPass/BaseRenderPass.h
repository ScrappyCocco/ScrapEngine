#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseRenderPass
		{
		protected:
			vk::RenderPass render_pass_;
		public:
			BaseRenderPass() = default;

			virtual ~BaseRenderPass() = 0;

			vk::RenderPass* get_render_pass();
		};
	}
}
