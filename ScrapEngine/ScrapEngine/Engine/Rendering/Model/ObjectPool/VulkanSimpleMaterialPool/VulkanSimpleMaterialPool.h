#pragma once

#include <unordered_map>
#include <memory>
#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Texture/Texture/BaseTexture.h>
#include <Engine/Rendering/Texture/TextureImageView/TextureImageView.h>
#include <Engine/Rendering/Texture/TextureSampler/TextureSampler.h>

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

			//This is the pool of BaseTexture objects
			//It associate the texture path with the corresponding object, as the other 2 texture pools here
			std::unordered_map<std::string, std::shared_ptr<BaseTexture>> base_texture_pool_;

			//This is the pool of the TextureImageView objects
			std::unordered_map<
				std::string,
				std::shared_ptr<TextureImageView>
			> texture_image_view_pool_;

			//This is the pool of the TextureSampler objects
			std::unordered_map<
				std::string,
				std::shared_ptr<TextureSampler>
			> texture_sampler_pool_;

			//This is the pool of the Pipelines
			//Currently made only of StandardVulkanGraphicsPipeline
			//The key of this pool is the string vertex_shader_path+fragment_shader_path
			std::unordered_map<
				std::string,
				std::shared_ptr<BaseVulkanGraphicsPipeline>
			> pipeline_pool_;
		public:
			//Singleton static function to get or create a class instance
			static VulkanSimpleMaterialPool* get_instance();

			std::shared_ptr<BaseVulkanGraphicsPipeline> get_pipeline(
				const std::string& vertex_shader_path,
				const std::string& fragment_shader_path,
				VulkanSwapChain* swap_chain,
				vk::DescriptorSetLayout* descriptor_set_layout);

			//Return or create the shared_ptr of the BaseTexture
			std::shared_ptr<BaseTexture> get_standard_texture(const std::string& texture_path);

			//Return or create the shared_ptr of the TextureSampler
			std::shared_ptr<TextureSampler> get_texture_sampler(const std::string& texture_path);

			//Return or create the shared_ptr of the TextureImageView
			std::shared_ptr<TextureImageView> get_texture_image_view(
				const std::string& texture_path);

			~VulkanSimpleMaterialPool();

			void clear_memory();
		};
	}
}
