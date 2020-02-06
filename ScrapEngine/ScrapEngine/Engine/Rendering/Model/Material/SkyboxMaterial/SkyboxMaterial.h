#pragma once

#include <Engine/Rendering/Model/Material/BasicMaterial.h>

namespace ScrapEngine
{
	namespace Render
	{
		class SkyboxUniformBuffer;
		class VulkanSwapChain;
		class BaseDescriptorPool;
		class TextureSampler;
		class TextureImageView;
		class BaseTexture;

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
