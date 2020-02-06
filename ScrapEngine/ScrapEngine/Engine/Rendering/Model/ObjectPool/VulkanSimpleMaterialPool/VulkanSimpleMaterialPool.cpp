#include <Engine/Rendering/Model/ObjectPool/VulkanSimpleMaterialPool/VulkanSimpleMaterialPool.h>
#include <Engine/Debug/DebugLog.h>
#include <numeric>
#include <Engine/Rendering/Model/Material/SimpleMaterial/SimpleMaterial.h>
#include <Engine/Rendering/Texture/Texture/StandardTexture/StandardTexture.h>
#include <Engine/Rendering/Pipeline/StandardPipeline/StandardVulkanGraphicsPipeline.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

//Init static instance reference

ScrapEngine::Render::VulkanSimpleMaterialPool* ScrapEngine::Render::VulkanSimpleMaterialPool::instance_ = nullptr;

ScrapEngine::Render::VulkanSimpleMaterialPool* ScrapEngine::Render::VulkanSimpleMaterialPool::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VulkanSimpleMaterialPool();
	}
	return instance_;
}

std::shared_ptr<ScrapEngine::Render::BaseVulkanGraphicsPipeline> ScrapEngine::Render::VulkanSimpleMaterialPool::
get_pipeline(const std::string& vertex_shader_path, const std::string& fragment_shader_path,
             VulkanSwapChain* swap_chain,
             vk::DescriptorSetLayout* descriptor_set_layout)
{
	const std::string key_string = vertex_shader_path + fragment_shader_path;
	if (pipeline_pool_.find(key_string) == pipeline_pool_.end())
	{
		// Pipeline not found, create it
		const vk::Extent2D swap_chain_extent = swap_chain->get_swap_chain_extent();
		pipeline_pool_[key_string] = std::make_shared<StandardVulkanGraphicsPipeline>(
			vertex_shader_path.c_str(),
			fragment_shader_path.c_str(),
			swap_chain_extent,
			descriptor_set_layout,
			VulkanDevice::get_instance()->
			get_msaa_samples());
		Debug::DebugLog::print_to_console_log("[VulkanSimpleMaterialPool] Pipeline loaded and created");
	}
	return pipeline_pool_[key_string];
}

std::shared_ptr<ScrapEngine::Render::BaseTexture> ScrapEngine::Render::VulkanSimpleMaterialPool::get_standard_texture(
	const std::string& texture_path)
{
	if (base_texture_pool_.find(texture_path) == base_texture_pool_.end())
	{
		// Texture not found, create it
		base_texture_pool_[texture_path] = std::make_shared<StandardTexture>(texture_path);
		Debug::DebugLog::print_to_console_log("[VulkanSimpleMaterialPool] Base Texture loaded and created");
	}
	return base_texture_pool_[texture_path];
}

std::shared_ptr<ScrapEngine::Render::TextureSampler> ScrapEngine::Render::VulkanSimpleMaterialPool::get_texture_sampler(
	const std::string& texture_path)
{
	if (texture_sampler_pool_.find(texture_path) == texture_sampler_pool_.end())
	{
		// Texture not found, create it
		const std::shared_ptr<BaseTexture> texture = get_standard_texture(texture_path);
		texture_sampler_pool_[texture_path] = std::make_shared<TextureSampler>(texture->get_mip_levels());
		Debug::DebugLog::print_to_console_log("[VulkanSimpleMaterialPool] Texture Sampler loaded and created");
	}
	return texture_sampler_pool_[texture_path];
}

std::shared_ptr<ScrapEngine::Render::TextureImageView> ScrapEngine::Render::VulkanSimpleMaterialPool::
get_texture_image_view(const std::string& texture_path)
{
	if (texture_image_view_pool_.find(texture_path) == texture_image_view_pool_.end())
	{
		// Texture not found, create it
		const std::shared_ptr<BaseTexture> texture = get_standard_texture(texture_path);
		texture_image_view_pool_[texture_path] = std::make_shared<TextureImageView>(
			texture->get_texture_image(),
			texture->get_mip_levels());
		Debug::DebugLog::print_to_console_log("[VulkanSimpleMaterialPool] Texture Image View loaded and created");
	}
	return texture_image_view_pool_[texture_path];
}

ScrapEngine::Render::VulkanSimpleMaterialPool::~VulkanSimpleMaterialPool()
{
	clear_memory();
}

void ScrapEngine::Render::VulkanSimpleMaterialPool::clear_memory()
{
	std::vector<std::string> texture_to_erase;
	for (const auto& texture : base_texture_pool_)
	{
		if (texture.second.use_count() == 1)
		{
			texture_to_erase.push_back(texture.first);
		}
	}
	for (const auto& texture_key : texture_to_erase)
	{
		Debug::DebugLog::print_to_console_log("[VulkanSimpleMaterialPool] Removing '"
			+ texture_key + "' shared material from pool memory");
		base_texture_pool_.erase(texture_key);
		texture_image_view_pool_.erase(texture_key);
		texture_sampler_pool_.erase(texture_key);
	}

	std::vector<std::string> pipeline_to_erase;
	for (const auto& pipeline : pipeline_pool_)
	{
		if (pipeline.second.use_count() == 1)
		{
			pipeline_to_erase.push_back(pipeline.first);
		}
	}
	for (const auto& pipeline_key : pipeline_to_erase)
	{
		Debug::DebugLog::print_to_console_log("[VulkanSimpleMaterialPool] Removing shared pipeline from pool memory");
		pipeline_pool_.erase(pipeline_key);
	}
}
