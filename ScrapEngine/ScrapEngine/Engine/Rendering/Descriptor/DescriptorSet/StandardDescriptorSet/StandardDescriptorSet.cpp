#include <Engine/Rendering/Descriptor/DescriptorSet/StandardDescriptorSet/StandardDescriptorSet.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::StandardDescriptorSet::StandardDescriptorSet() : BaseDescriptorSet()
{
	const vk::DescriptorSetLayoutBinding ubo_layout_binding(
		0,
		vk::DescriptorType::eUniformBuffer,
		1,
		vk::ShaderStageFlagBits::eVertex,
		nullptr
	);

	const vk::DescriptorSetLayoutBinding sampler_layout_binding(
		1,
		vk::DescriptorType::eCombinedImageSampler,
		1,
		vk::ShaderStageFlagBits::eFragment,
		nullptr
	);

	std::array<vk::DescriptorSetLayoutBinding, 2> bindings = {ubo_layout_binding, sampler_layout_binding};

	vk::DescriptorSetLayoutCreateInfo layout_info(
		vk::DescriptorSetLayoutCreateFlags(),
		static_cast<uint32_t>(bindings.size()),
		bindings.data()
	);

	if (VulkanDevice::get_instance()->get_logical_device()->createDescriptorSetLayout(
			&layout_info, nullptr, &descriptor_set_layout_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("VulkanDescriptorSet: Failed to create descriptor set layout!");
	}
}

void ScrapEngine::Render::StandardDescriptorSet::create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
                                                                      const std::vector<vk::Image>* swap_chain_images,
                                                                      const std::vector<vk::Buffer>* uniform_buffers,
                                                                      vk::ImageView* texture_image_view,
                                                                      vk::Sampler* texture_sampler,
                                                                      const vk::DeviceSize& buffer_info_size)
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
		throw std::runtime_error("DescriptorSetLayout: Failed to allocate descriptor sets!");
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
