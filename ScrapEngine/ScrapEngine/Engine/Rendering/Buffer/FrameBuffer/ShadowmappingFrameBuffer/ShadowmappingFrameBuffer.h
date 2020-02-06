#pragma once

#include <Engine/Rendering/Buffer/FrameBuffer/BaseFrameBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseRenderPass;
		class ShadowmappingFrameBufferAttachment;

		class ShadowmappingFrameBuffer : public BaseFrameBuffer
		{
		private:
			int32_t width_, height_;
			ShadowmappingFrameBufferAttachment* depth_attachment_ = nullptr;
			vk::Sampler depth_sampler_;
		public:
			ShadowmappingFrameBuffer(int32_t width, int32_t height, vk::Format depth_format,
			                         vk::Filter shadowmap_filter, BaseRenderPass* render_pass);
			~ShadowmappingFrameBuffer();

			vk::Sampler* get_depth_sampler();
			ShadowmappingFrameBufferAttachment* get_depth_attachment() const;
		};
	}
}
