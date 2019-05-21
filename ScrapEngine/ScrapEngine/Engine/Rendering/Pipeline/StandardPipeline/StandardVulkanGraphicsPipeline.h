#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Shader/ShaderManager.h>
#include <Engine/Rendering/Pipeline/BaseVulkanGraphicsPipeline.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardVulkanGraphicsPipeline : public BaseVulkanGraphicsPipeline
		{
		private:
			ShaderManager* shader_manager_ref_ = nullptr;
		public:
			StandardVulkanGraphicsPipeline(const char* vertex_shader, const char* fragment_shader,
			                       vk::Extent2D* swap_chain_extent,
			                       vk::DescriptorSetLayout* descriptor_set_layout, vk::SampleCountFlagBits msaa_samples);
			~StandardVulkanGraphicsPipeline() = default;
		};
	}
}
