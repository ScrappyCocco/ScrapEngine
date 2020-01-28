#pragma once

#include <Engine/Rendering/RenderPass/BaseRenderPass.h>

namespace ScrapEngine
{
	namespace Render
	{
		class ShadowmappingRenderPass : public BaseRenderPass
		{
		public:
			ShadowmappingRenderPass(const vk::Format& depth_format);

			~ShadowmappingRenderPass() = default;
		};
	}
}
