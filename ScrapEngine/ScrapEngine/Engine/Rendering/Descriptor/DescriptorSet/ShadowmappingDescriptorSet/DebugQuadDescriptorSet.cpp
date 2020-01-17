#include <Engine/Rendering/Descriptor/DescriptorSet/ShadowmappingDescriptorSet/DebugQuadDescriptorSet.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::DebugQuadDescriptorSet::DebugQuadDescriptorSet(vk::DescriptorSetLayout* layout)
{
	vk::PipelineLayoutCreateInfo create_info(
		vk::PipelineLayoutCreateFlags(),
		1,
		layout
	);

	if (VulkanDevice::get_instance()->get_logical_device()->createPipelineLayout(
			&create_info, nullptr, &pipeline_layout_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("DebugQuadDescriptorSet: Failed to create pipeline layout!");
	}
}

void ScrapEngine::Render::DebugQuadDescriptorSet::create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
	const std::vector<vk::Image>* swap_chain_images, const std::vector<vk::Buffer>* uniform_buffers,
	vk::ImageView* texture_image_view, vk::Sampler* texture_sampler, const vk::DeviceSize& buffer_info_size)
{
	std::vector<vk::DescriptorSetLayout> layouts(swap_chain_images->size(), descriptor_set_layout_);

	vk::DescriptorSetAllocateInfo alloc_info(
		*descriptor_pool,
		static_cast<uint32_t>(swap_chain_images->size()),
		layouts.data()
	);

	descriptor_sets_.resize(swap_chain_images->size());

	if (VulkanDevice::get_instance()->get_logical_device()->allocateDescriptorSets(&alloc_info, &descriptor_sets_[0])
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("ShadowmappingDescriptorSet - DescriptorSetLayout: Failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < swap_chain_images->size(); i++)
	{
		vk::DescriptorBufferInfo buffer_info(
			(*uniform_buffers)[i],
			0,
			buffer_info_size
		);

		vk::DescriptorImageInfo image_info(
			*texture_sampler,
			*texture_image_view,
			vk::ImageLayout::eShaderReadOnlyOptimal
		);

		std::array<vk::WriteDescriptorSet, 2> descriptor_writes = {
			vk::WriteDescriptorSet(
				descriptor_sets_[i],
				0,
				0,
				1,
				vk::DescriptorType::eUniformBuffer,
				nullptr,
				&buffer_info
			),
			vk::WriteDescriptorSet(
				descriptor_sets_[i],
				1,
				0,
				1,
				vk::DescriptorType::eCombinedImageSampler,
				&image_info
			)
		};

		VulkanDevice::get_instance()->get_logical_device()->updateDescriptorSets(
			static_cast<uint32_t>(descriptor_writes.size()),
			descriptor_writes.data(), 0, nullptr);
	}
}
