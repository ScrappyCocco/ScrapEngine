#pragma once

#include <Engine/Rendering/Model/Material/BasicMaterial.h>
#include <Engine/Rendering/Texture/TextureSampler/TextureSampler.h>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/VulkanDescriptorPool.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>

namespace ScrapEngine
{
	namespace Render
	{
		class SkyboxMaterial : public BasicMaterial
		{
		private:
			BaseTexture* skybox_texture_ = nullptr;
			TextureImageView* vulkan_texture_image_view_ = nullptr;
			TextureSampler* vulkan_texture_sampler_ = nullptr;
			VulkanDescriptorPool* vulkan_render_descriptor_pool_ = nullptr;
		public:
			SkyboxMaterial() = default;
			~SkyboxMaterial();

			void create_pipeline(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                     VulkanSwapChain* swap_chain);

			void create_skybox_texture(const std::array<std::string, 6>& textures_path);

			void create_descriptor_sets(VulkanSwapChain* swap_chain,
			                            UniformBuffer* uniform_buffer);
		};
	}
}
