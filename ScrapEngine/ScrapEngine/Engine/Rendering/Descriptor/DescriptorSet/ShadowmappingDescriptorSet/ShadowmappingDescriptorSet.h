#pragma once

#include <Engine/Rendering/Descriptor/DescriptorSet/BaseDescriptorSet.h>

namespace ScrapEngine
{
	namespace Render
	{
		class ShadowmappingDescriptorSet : public BaseDescriptorSet
		{
		public:
			ShadowmappingDescriptorSet();
			~ShadowmappingDescriptorSet() = default;

			void create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
			                            size_t swap_chain_images_size,
			                            const std::vector<vk::Buffer>* uniform_buffers,
			                            const vk::DeviceSize& buffer_info_size);
		};
	}
}
