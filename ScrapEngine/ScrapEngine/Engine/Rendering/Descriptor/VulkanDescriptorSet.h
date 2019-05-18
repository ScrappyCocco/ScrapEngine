#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h"

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanDescriptorSet
		{
		private:
			vk::DescriptorSetLayout descriptor_set_layout_;
			vk::PipelineLayout pipeline_layout_;
			std::vector<vk::DescriptorSet> descriptor_sets_;
		public:
			VulkanDescriptorSet();
			~VulkanDescriptorSet();

			void create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
			                            const std::vector<vk::Image>* swap_chain_images,
			                            const std::vector<vk::Buffer>* uniform_buffers,
			                            vk::ImageView* texture_image_view, vk::Sampler* texture_sampler,
			                            const vk::DeviceSize& buffer_info_size = sizeof(UniformBufferObject));

			vk::DescriptorSetLayout* get_descriptor_set_layout();
			vk::PipelineLayout* get_pipeline_layout();
			const std::vector<vk::DescriptorSet>* get_descriptor_sets() const;
		};
	}
}
