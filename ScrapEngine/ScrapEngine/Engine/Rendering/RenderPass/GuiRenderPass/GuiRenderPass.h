#pragma once

#include <Engine/Rendering/RenderPass/BaseRenderPass.h>

namespace ScrapEngine
{
	namespace Render
	{
		class GuiRenderPass : public BaseRenderPass
		{
		public:
			GuiRenderPass(const vk::Format& swap_chain_image_format, vk::SampleCountFlagBits msaa_samples);

			~GuiRenderPass() = default;
		};
	}
}
