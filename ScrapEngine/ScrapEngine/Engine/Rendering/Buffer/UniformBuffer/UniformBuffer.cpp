#include "UniformBuffer.h"
#include "../../../Debug/DebugLog.h"
#include "../BaseBuffer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Engine/Rendering/Device/VulkanDevice.h"

ScrapEngine::Render::UniformBuffer::UniformBuffer(const std::vector<vk::Image>* swap_chain_images, const vk::Extent2D& input_swap_chain_extent)
	: swap_chain_extent_(input_swap_chain_extent)
{
	const vk::DeviceSize buffer_size(sizeof(UniformBufferObject));

	swap_chain_images_size_ = swap_chain_images->size();
	uniform_buffers_.resize(swap_chain_images_size_);
	uniform_buffers_memory_.resize(swap_chain_images_size_);

	for (size_t i = 0; i < swap_chain_images_size_; i++) {
		BaseBuffer::create_buffer(buffer_size, vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, uniform_buffers_[i], uniform_buffers_memory_[i]);
	}
	//Map memory
	mapped_memory_.resize(swap_chain_images_size_);
	for (size_t i = 0; i < swap_chain_images_size_; i++) {
		VulkanDevice::StaticLogicDeviceRef->mapMemory(uniform_buffers_memory_[i], 0, sizeof(UniformBufferObject), vk::MemoryMapFlags(), &mapped_memory_[i]);
	}
}

ScrapEngine::Render::UniformBuffer::~UniformBuffer()
{
	for (size_t i = 0; i < swap_chain_images_size_; i++) {
		VulkanDevice::StaticLogicDeviceRef->destroyBuffer(uniform_buffers_[i]);
		VulkanDevice::StaticLogicDeviceRef->unmapMemory(uniform_buffers_memory_[i]);
		VulkanDevice::StaticLogicDeviceRef->freeMemory(uniform_buffers_memory_[i]);
	}
}

void ScrapEngine::Render::UniformBuffer::update_uniform_buffer(const uint32_t& current_image, const ScrapEngine::Transform& object_transform, ScrapEngine::Render::Camera* render_camera)
{
	UniformBufferObject ubo = {};

	ubo.model = glm::translate(glm::mat4(1.0f), object_transform.location);
	ubo.model = glm::scale(ubo.model, object_transform.scale);
	if (object_transform.rotation.x != 0 || object_transform.rotation.y != 0 || object_transform.rotation.z != 0) {
		ubo.model = glm::rotate(ubo.model, glm::radians(90.0f), object_transform.rotation);
	}
	ubo.proj = glm::perspective(glm::radians(45.0f), swap_chain_extent_.width / (float)swap_chain_extent_.height, render_camera->get_camera_min_draw_distance(), render_camera->get_camera_max_draw_distance());
	ubo.view = glm::lookAt(render_camera->get_camera_location(), render_camera->get_camera_location() + render_camera->get_camera_front(), render_camera->get_camera_up());
	ubo.proj[1][1] *= -1; //Invert image for openGL style
	
	memcpy(mapped_memory_[current_image], &ubo, sizeof(ubo));
}

const std::vector<vk::Buffer>* ScrapEngine::Render::UniformBuffer::get_uniform_buffers() const
{
	return &uniform_buffers_;
}

const std::vector<vk::DeviceMemory>* ScrapEngine::Render::UniformBuffer::get_uniform_buffers_memory() const
{
	return &uniform_buffers_memory_;
}

