#pragma once

#include <Engine/Rendering/Model/Material/BasicMaterial.h>
#include <Engine/Rendering/Texture/TextureSampler/TextureSampler.h>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/BaseDescriptorPool.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>
#include <Engine/Rendering/Buffer/UniformBuffer/SkyboxUniformBuffer/SkyboxUniformBuffer.h>

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
			BaseDescriptorPool* vulkan_render_descriptor_pool_ = nullptr;
		public:
			SkyboxMaterial();
			~SkyboxMaterial();

			void create_pipeline(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                     VulkanSwapChain* swap_chain);

			void create_skybox_texture(const std::array<std::string, 6>& textures_path);

			void create_descriptor_sets(VulkanSwapChain* swap_chain,
			                            SkyboxUniformBuffer* uniform_buffer);
		};
	}
}
