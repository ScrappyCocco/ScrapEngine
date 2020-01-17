#pragma once

#include <Engine/Rendering/Descriptor/DescriptorSet/BaseDescriptorSet.h>
#include <Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class DebugQuadDescriptorSet : public BaseDescriptorSet
		{
		public:
			DebugQuadDescriptorSet(vk::DescriptorSetLayout* layout);
			~DebugQuadDescriptorSet() = default;

			void create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
				const std::vector<vk::Image>* swap_chain_images,
				const std::vector<vk::Buffer>* uniform_buffers,
				vk::ImageView* texture_image_view, vk::Sampler* texture_sampler,
				const vk::DeviceSize& buffer_info_size = sizeof(UniformBufferObject));
		};
	}
}
