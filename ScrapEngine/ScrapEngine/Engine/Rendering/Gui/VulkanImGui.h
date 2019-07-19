#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Texture/TextureSampler/TextureSampler.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/VulkanDescriptorPool.h>
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
		private:
			vk::Image front_image_;
			vk::DeviceMemory font_memory_;
			TextureImageView* front_view_ = nullptr;
			TextureSampler* sampler_ = nullptr;
			VulkanDescriptorPool* descriptor_pool_ = nullptr;
			GuiDescriptorSet* descriptor_set_ = nullptr;
			GuiVulkanGraphicsPipeline* pipeline_ = nullptr;
			//Buffers
			GenericBuffer* vertex_buffer_;
			GenericBuffer* index_buffer_;
			int32_t vertex_count_ = 0;
			int32_t index_count_ = 0;

			struct PushConstBlock {
				glm::vec2 scale;
				glm::vec2 translate;
			} push_const_block_;
		public:
			VulkanImGui();
			~VulkanImGui();

			void init(float width, float height);

			void init_resources(VulkanSwapChain* swap_chain);

			void new_frame();

			void update_buffers();
		};

	}
}
