#pragma once

#include <Engine/Rendering/Model/Material/BasicMaterial.h>
#include <Engine/Rendering/Texture/TextureSampler/TextureSampler.h>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/BaseDescriptorPool.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Buffer/UniformBuffer/StandardUniformBuffer/StandardUniformBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class SimpleMaterial : public BasicMaterial
		{
		private:
			std::shared_ptr<BaseTexture> vulkan_texture_image_ = nullptr;
			std::shared_ptr<TextureImageView> vulkan_texture_image_view_ = nullptr;
			std::shared_ptr<TextureSampler> vulkan_texture_sampler_ = nullptr;
			BaseDescriptorPool* vulkan_render_descriptor_pool_ = nullptr;
		public:
			SimpleMaterial();
			~SimpleMaterial();

			void create_pipeline(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
			                     VulkanSwapChain* swap_chain);

			void create_texture(const std::string& texture_path);

			void create_descriptor_sets(VulkanSwapChain* swap_chain,
			                            StandardUniformBuffer* uniform_buffer);
		};
	}
}
