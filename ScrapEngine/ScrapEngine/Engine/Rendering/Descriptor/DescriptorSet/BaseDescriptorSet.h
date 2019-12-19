#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseDescriptorSet
		{
		protected:
			vk::DescriptorSetLayout descriptor_set_layout_;
			vk::PipelineLayout pipeline_layout_;
			std::vector<vk::DescriptorSet> descriptor_sets_;
		public:
			BaseDescriptorSet() = default;
			virtual ~BaseDescriptorSet() = 0;

			vk::DescriptorSetLayout* get_descriptor_set_layout();
			vk::PipelineLayout* get_pipeline_layout();
			const std::vector<vk::DescriptorSet>* get_descriptor_sets() const;
		};
	}
}
