#pragma once

#include <Engine/Rendering/Buffer/FrameBuffer/BaseFrameBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanImageView;

		class StandardFrameBuffer : public BaseFrameBuffer
		{
		public:
			StandardFrameBuffer(VulkanImageView* input_image_view_ref,
			                    const vk::Extent2D* input_swap_chain_extent,
			                    vk::ImageView* depth_image_view, vk::ImageView* color_image_view);

			~StandardFrameBuffer() = default;
		};
	}
}
