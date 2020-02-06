#pragma once

#include <Engine/Rendering/Buffer/CommandBuffer/BaseCommandBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanImGui;
		class BaseFrameBuffer;
		class BaseRenderPass;

		class GuiCommandBuffer : public BaseCommandBuffer
		{
		private:
			BaseRenderPass* render_pass_ref_ = nullptr;
		public:
			explicit GuiCommandBuffer(BaseRenderPass* render_pass, VulkanCommandPool* command_pool);

			~GuiCommandBuffer() = default;

			void init_command_buffer(BaseFrameBuffer* swap_chain_frame_buffer,
			                         const vk::Extent2D& input_swap_chain_extent_ref,
			                         uint32_t current_image);

			void load_ui(VulkanImGui* gui);
		};
	}
}
