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
			std::vector<vk::DescriptorSet> descriptor_sets_;
		public:
			BaseDescriptorSet() = default;
			virtual ~BaseDescriptorSet() = 0;

			void write_image_info(vk::DescriptorImageInfo image_info, uint32_t dst_binding = 0);
			void write_buffer_info(vk::DescriptorBufferInfo buffer_info, uint32_t dst_binding = 0);

			vk::DescriptorSetLayout* get_descriptor_set_layout();
			const std::vector<vk::DescriptorSet>* get_descriptor_sets() const;
		};
	}
}
