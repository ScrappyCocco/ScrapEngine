#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/RenderPass/VulkanRenderPass.h>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Texture/TextureSampler/TextureSampler.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/VulkanDescriptorPool.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Descriptor/DescriptorSet/GuiDescriptorSet/GuiDescriptorSet.h>

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

			struct PushConstBlock {
				glm::vec2 scale;
				glm::vec2 translate;
			} push_const_block_;
		public:
			VulkanImGui();
			~VulkanImGui();

			void init(float width, float height);

			void init_resources(VulkanRenderPass* render_pass, VkQueue copy_queue, VulkanSwapChain* swap_chain);
		};

	}
}
