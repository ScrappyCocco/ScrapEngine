#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class ShadowmappingFrameBufferAttachment
		{
		private:
			vk::Image image_;
			VmaAllocation image_memory_;
			vk::ImageView image_view_;
		public:
			ShadowmappingFrameBufferAttachment(int32_t width, int32_t height, vk::Format depth_format);
			~ShadowmappingFrameBufferAttachment();

			vk::Image* get_image();
			vk::ImageView* get_image_view();
		};
	}
}
