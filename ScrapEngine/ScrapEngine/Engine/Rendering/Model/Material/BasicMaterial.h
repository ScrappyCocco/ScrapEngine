#pragma once
#include <Engine/Rendering/Texture/TextureSampler.h>
#include <Engine/Rendering/Texture/TextureImageView.h>
#include <Engine/Rendering/Texture/TextureImage.h>
#include <Engine/Rendering/Pipeline/VulkanGraphicsPipeline.h>
#include <Engine/Rendering/Descriptor/VulkanDescriptorPool.h>
#include <Engine/Rendering/Descriptor/VulkanDescriptorSet.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanGraphicsPipeline;
		class TextureImage;
		class TextureImageView;
		class TextureSampler;

		class BasicMaterial
		{
		private:
			ScrapEngine::Render::VulkanGraphicsPipeline* vulkan_render_graphics_pipeline_ = nullptr;
			ScrapEngine::Render::TextureImage* vulkan_texture_image_ = nullptr;
			ScrapEngine::Render::TextureImageView* vulkan_texture_image_view_ = nullptr;
			ScrapEngine::Render::TextureSampler* vulkan_texture_sampler_ = nullptr;
			ScrapEngine::Render::VulkanDescriptorPool* vulkan_render_descriptor_pool_ = nullptr;
			ScrapEngine::Render::VulkanDescriptorSet* vulkan_render_descriptor_set_ = nullptr;
		public:
			BasicMaterial();
			~BasicMaterial();

			void create_pipeline(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                     ScrapEngine::Render::VulkanSwapChain* swap_chain,
			                     ScrapEngine::Render::VulkanDevice* render_device);
			void delete_graphics_pipeline();

			void create_texture(const std::string& texture_path);

			void create_descriptor_sets(ScrapEngine::Render::VulkanSwapChain* swap_chain,
			                            ScrapEngine::Render::UniformBuffer* uniform_buffer);

			ScrapEngine::Render::VulkanGraphicsPipeline* get_vulkan_render_graphics_pipeline() const;
			ScrapEngine::Render::VulkanDescriptorSet* get_vulkan_render_descriptor_set() const;
		};
	}
}
