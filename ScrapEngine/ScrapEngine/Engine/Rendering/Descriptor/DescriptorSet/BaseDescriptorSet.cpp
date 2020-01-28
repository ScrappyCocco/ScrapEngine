#include <Engine/Rendering/Descriptor/DescriptorSet/BaseDescriptorSet.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::BaseDescriptorSet::~BaseDescriptorSet()
{
	VulkanDevice::get_instance()->get_logical_device()->destroyDescriptorSetLayout(descriptor_set_layout_);
}

void ScrapEngine::Render::BaseDescriptorSet::write_image_info(vk::DescriptorImageInfo image_info,
                                                              const uint32_t dst_binding)
{
	for (auto& descriptor : descriptor_sets_)
	{
		std::array<vk::WriteDescriptorSet, 1> descriptor_writes = {
			vk::WriteDescriptorSet(
				descriptor,
				dst_binding,
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

void ScrapEngine::Render::BaseDescriptorSet::write_buffer_info(vk::DescriptorBufferInfo buffer_info,
                                                               const uint32_t dst_binding)
{
	for (auto& descriptor : descriptor_sets_)
	{
		std::array<vk::WriteDescriptorSet, 1> descriptor_writes = {
			vk::WriteDescriptorSet(
				descriptor,
				dst_binding,
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

vk::DescriptorSetLayout* ScrapEngine::Render::BaseDescriptorSet::get_descriptor_set_layout()
{
	return &descriptor_set_layout_;
}

const std::vector<vk::DescriptorSet>* ScrapEngine::Render::BaseDescriptorSet::get_descriptor_sets() const
{
	return &descriptor_sets_;
}
