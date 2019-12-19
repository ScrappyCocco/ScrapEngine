#pragma once

#include <Engine/Rendering/VulkanInclude.h>

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
