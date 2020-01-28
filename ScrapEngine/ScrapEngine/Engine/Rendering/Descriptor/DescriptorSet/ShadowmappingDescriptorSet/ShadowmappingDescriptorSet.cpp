#include <Engine/Rendering/Descriptor/DescriptorSet/ShadowmappingDescriptorSet/ShadowmappingDescriptorSet.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::ShadowmappingDescriptorSet::ShadowmappingDescriptorSet()
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

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createDescriptorSetLayout(
		&layout_info, nullptr, &descriptor_set_layout_);

	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "ShadowmappingDescriptorSet: Failed to create descriptor set layout!");
	}
}

void ScrapEngine::Render::ShadowmappingDescriptorSet::create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
                                                                             const size_t swap_chain_images_size,
                                                                             const std::vector<vk::Buffer>*
                                                                             uniform_buffers,
                                                                             const vk::DeviceSize& buffer_info_size)
{
	std::vector<vk::DescriptorSetLayout> layouts(swap_chain_images_size, descriptor_set_layout_);

	vk::DescriptorSetAllocateInfo alloc_info(
		*descriptor_pool,
		static_cast<uint32_t>(swap_chain_images_size),
		layouts.data()
	);

	descriptor_sets_.resize(swap_chain_images_size);

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->allocateDescriptorSets(
		&alloc_info, &descriptor_sets_[0]);
	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "ShadowmappingDescriptorSet - DescriptorSetLayout: Failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < swap_chain_images_size; i++)
	{
		vk::DescriptorBufferInfo buffer_info(
			(*uniform_buffers)[i],
			0,
			buffer_info_size
		);

		std::array<vk::WriteDescriptorSet, 1> descriptor_writes = {
			vk::WriteDescriptorSet(
				descriptor_sets_[i],
				0,
				0,
				1,
				vk::DescriptorType::eUniformBuffer,
				nullptr,
				&buffer_info
			)
		};

		VulkanDevice::get_instance()->get_logical_device()->updateDescriptorSets(
			static_cast<uint32_t>(descriptor_writes.size()),
			descriptor_writes.data(), 0, nullptr);
	}
}
