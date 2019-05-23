#pragma once
#include <unordered_map>
#include <memory>
#include <Engine/Rendering/Model/Material/BasicMaterial.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include "Engine/Rendering/Texture/Texture/BaseTexture.h"
#include "Engine/Rendering/Texture/TextureImageView/TextureImageView.h"
#include "Engine/Rendering/Texture/TextureSampler/TextureSampler.h"

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanSimpleMaterialPool
		{
		private:
			//Singleton static instance
			static VulkanSimpleMaterialPool* instance_;

			//The constructor is private because this class is a Singleton
			VulkanSimpleMaterialPool() = default;

			std::unordered_map<std::string, std::shared_ptr<ScrapEngine::Render::BaseTexture>> base_texture_pool_;
			std::unordered_map<
				std::string,
				std::shared_ptr<ScrapEngine::Render::TextureImageView>
			> texture_image_view_pool_;
			std::unordered_map<
				std::string,
				std::shared_ptr<ScrapEngine::Render::TextureSampler>
			> texture_sampler_pool_;
			std::unordered_map<
				std::string,
				std::shared_ptr<ScrapEngine::Render::BaseVulkanGraphicsPipeline>
			> pipeline_pool_;
		public:
			//Singleton static function to get or create a class instance
			static VulkanSimpleMaterialPool* get_instance();

			std::shared_ptr<ScrapEngine::Render::BaseVulkanGraphicsPipeline> get_pipeline(
				const std::string& vertex_shader_path,
				const std::string& fragment_shader_path,
				ScrapEngine::Render::VulkanSwapChain* swap_chain,
				vk::DescriptorSetLayout* descriptor_set_layout);

			std::shared_ptr<ScrapEngine::Render::BaseTexture> get_standard_texture(const std::string& texture_path);

			std::shared_ptr<ScrapEngine::Render::TextureSampler> get_texture_sampler(const std::string& texture_path);

			std::shared_ptr<ScrapEngine::Render::TextureImageView> get_texture_image_view(
				const std::string& texture_path);

			~VulkanSimpleMaterialPool();

			void clear_memory();
		};
	}
}
