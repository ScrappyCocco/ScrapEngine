#pragma once

#include <Engine/Rendering/Buffer/CommandBuffer/BaseCommandBuffer.h>
#include <Engine/Rendering/Buffer/FrameBuffer/VulkanFrameBuffer.h>
#include <Engine/Rendering/Gui/VulkanImGui.h>
#include <Engine/Rendering/RenderPass/BaseRenderPass.h>


namespace ScrapEngine
{
	namespace Render
	{
		class GuiCommandBuffer : public BaseCommandBuffer
		{
		private:
			BaseRenderPass* render_pass_ref_ = nullptr;
		public:
			explicit GuiCommandBuffer(BaseRenderPass* render_pass, VulkanCommandPool* command_pool);

			~GuiCommandBuffer() = default;

			void init_command_buffer(VulkanFrameBuffer* swap_chain_frame_buffer,
			                         vk::Extent2D* input_swap_chain_extent_ref,
			                         uint32_t current_image);

			void load_ui(VulkanImGui* gui);
		};
	}
}
