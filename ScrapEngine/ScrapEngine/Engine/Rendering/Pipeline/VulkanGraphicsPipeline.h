#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Shader/ShaderManager.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanGraphicsPipeline
		{
		private:
			ShaderManager* shader_manager_ref_ = nullptr;
			vk::PipelineLayout pipeline_layout_;
			vk::Pipeline graphics_pipeline_;
		public:
			VulkanGraphicsPipeline(const char* vertex_shader, const char* fragment_shader,
			                       vk::Extent2D* swap_chain_extent,
			                       vk::DescriptorSetLayout* descriptor_set_layout, vk::SampleCountFlagBits msaa_samples,
			                       bool is_skybox = false);
			~VulkanGraphicsPipeline();

			vk::Pipeline* get_graphics_pipeline();
			vk::PipelineLayout* get_pipeline_layout();
		};
	}
}
