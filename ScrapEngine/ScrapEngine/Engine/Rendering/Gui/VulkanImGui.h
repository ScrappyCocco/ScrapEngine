#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Texture/TextureSampler/TextureSampler.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/BaseDescriptorPool.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Descriptor/DescriptorSet/GuiDescriptorSet/GuiDescriptorSet.h>
#include <Engine/Rendering/Pipeline/GuiPipeline/GuiVulkanGraphicsPipeline.h>
#include <Engine/Rendering/Buffer/GenericBuffer/GenericBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanImGui
		{
		public:
			struct PushConstBlock
			{
				glm::vec2 scale;
				glm::vec2 translate;
			};

		private:
			vk::Image front_image_;
			vk::DeviceMemory font_memory_;
			TextureImageView* front_view_ = nullptr;
			TextureSampler* sampler_ = nullptr;
			BaseDescriptorPool* descriptor_pool_ = nullptr;
			GuiDescriptorSet* descriptor_set_ = nullptr;
			GuiVulkanGraphicsPipeline* pipeline_ = nullptr;
			//Buffers
			//I need vectors because i need one for each command buffer (2 in total)
			GenericBuffer* vertex_buffer_;
			GenericBuffer* index_buffer_;
			int32_t vertex_count_;
			int32_t index_count_;

			PushConstBlock push_const_block_;
		public:
			explicit VulkanImGui();
			~VulkanImGui();

			void init(float width, float height);
			void init_resources(VulkanSwapChain* swap_chain, BaseRenderPass* render_pass);

			void update_buffers();

			void generate_empty_gui_frame() const;
			void generate_loading_gui_frame() const;
			void pre_gui_frame() const;
			void post_gui_frame() const;

			void loading_ui() const;

			GuiDescriptorSet* get_descriptor_set() const;
			GuiVulkanGraphicsPipeline* get_pipeline() const;
			GenericBuffer* get_vertex_buffer() const;
			GenericBuffer* get_index_buffer() const;
			PushConstBlock* get_push_const_block();
		};
	}
}
