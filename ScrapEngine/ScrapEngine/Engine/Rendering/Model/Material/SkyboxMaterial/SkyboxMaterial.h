#pragma once

#include <Engine/Rendering/Model/Material/BasicMaterial.h>
#include <Engine/Rendering/Texture/TextureSampler/TextureSampler.h>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Descriptor/VulkanDescriptorPool.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>

namespace ScrapEngine
{
	namespace Render
	{
		class SkyboxMaterial : public BasicMaterial
		{
		private:
			ScrapEngine::Render::BaseTexture* skybox_texture_ = nullptr;
			ScrapEngine::Render::TextureImageView* vulkan_texture_image_view_ = nullptr;
			ScrapEngine::Render::TextureSampler* vulkan_texture_sampler_ = nullptr;
			ScrapEngine::Render::VulkanDescriptorPool* vulkan_render_descriptor_pool_ = nullptr;
		public:
			SkyboxMaterial() = default;
			~SkyboxMaterial();

			void create_pipeline(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                     ScrapEngine::Render::VulkanSwapChain* swap_chain);

			void create_skybox_texture(const std::array<std::string, 6>& textures_path);

			void create_descriptor_sets(ScrapEngine::Render::VulkanSwapChain* swap_chain,
			                            ScrapEngine::Render::UniformBuffer* uniform_buffer);
		};
	}
}
