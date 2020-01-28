#pragma once

#include <Engine/Rendering/Descriptor/DescriptorSet/BaseDescriptorSet.h>
#include <Engine/Rendering/Buffer/UniformBuffer/StandardUniformBuffer/StandardUniformBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardDescriptorSet : public BaseDescriptorSet
		{
		public:
			StandardDescriptorSet();
			~StandardDescriptorSet() = default;

			void create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
			                            size_t swap_chain_images_size,
			                            const std::vector<vk::Buffer>* uniform_buffers,
			                            vk::ImageView* texture_image_view, vk::Sampler* texture_sampler,
			                            const vk::DeviceSize& buffer_info_size = sizeof(UniformBufferObject));
		};
	}
}
