#pragma once

#include <Engine/Rendering/RenderPass/BaseRenderPass.h>

namespace ScrapEngine
{
	namespace Render
	{
		class ShadowmappingRenderPass : public BaseRenderPass
		{
		public:
			ShadowmappingRenderPass() = default;

			void init(const vk::Format& depth_format);

			~ShadowmappingRenderPass() = default;
		};
	}
}
