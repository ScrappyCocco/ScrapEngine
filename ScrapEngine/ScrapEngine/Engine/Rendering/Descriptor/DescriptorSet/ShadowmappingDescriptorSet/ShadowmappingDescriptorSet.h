#pragma once

#include <Engine/Rendering/Descriptor/DescriptorSet/BaseDescriptorSet.h>

namespace ScrapEngine
{
	namespace Render
	{
		class ShadowmappingDescriptorSet : public BaseDescriptorSet
		{
		public:
			ShadowmappingDescriptorSet(vk::DescriptorSetLayout* layout);
			~ShadowmappingDescriptorSet() = default;

			void create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
			                            const std::vector<vk::Image>* swap_chain_images,
			                            const std::vector<vk::Buffer>* uniform_buffers,
			                            const vk::DeviceSize& buffer_info_size);
		};
	}
}
