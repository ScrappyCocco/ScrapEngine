#pragma once

#include <Engine/Rendering/Buffer/FrameBuffer/BaseFrameBuffer.h>
#include <Engine/Rendering/Buffer/FrameBuffer/ShadowmappingFrameBuffer/ShadowmappingFrameBufferAttachment.h>
#include <Engine/Rendering/RenderPass/BaseRenderPass.h>

namespace ScrapEngine
{
	namespace Render
	{
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
		};
	}
}
