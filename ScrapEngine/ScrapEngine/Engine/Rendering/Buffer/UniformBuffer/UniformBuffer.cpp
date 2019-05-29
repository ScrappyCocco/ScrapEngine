#include <Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::UniformBuffer::UniformBuffer(const std::vector<vk::Image>* swap_chain_images,
                                                  const vk::Extent2D& input_swap_chain_extent)
	: swap_chain_extent_(input_swap_chain_extent)
{
	const vk::DeviceSize buffer_size(sizeof(UniformBufferObject));

	swap_chain_images_size_ = swap_chain_images->size();
	uniform_buffers_.resize(swap_chain_images_size_);
	uniform_buffers_memory_.resize(swap_chain_images_size_);

	for (size_t i = 0; i < swap_chain_images_size_; i++)
	{
		BaseBuffer::create_buffer(buffer_size, vk::BufferUsageFlagBits::eUniformBuffer,
		                          vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
		                          uniform_buffers_[i], uniform_buffers_memory_[i]);
	}
	//Map memory
	mapped_memory_.resize(swap_chain_images_size_);
	for (size_t i = 0; i < swap_chain_images_size_; i++)
	{
		VulkanDevice::get_instance()->get_logical_device()->mapMemory(uniform_buffers_memory_[i], 0,
		                                                              sizeof(UniformBufferObject),
		                                                              vk::MemoryMapFlags(), &mapped_memory_[i]);
	}
}

ScrapEngine::Render::UniformBuffer::~UniformBuffer()
{
	for (size_t i = 0; i < swap_chain_images_size_; i++)
	{
		VulkanDevice::get_instance()->get_logical_device()->destroyBuffer(uniform_buffers_[i]);
		VulkanDevice::get_instance()->get_logical_device()->unmapMemory(uniform_buffers_memory_[i]);
		VulkanDevice::get_instance()->get_logical_device()->freeMemory(uniform_buffers_memory_[i]);
	}
}

void ScrapEngine::Render::UniformBuffer::update_uniform_buffer(const uint32_t& current_image,
                                                               const Core::STransform& object_transform,
                                                               Camera* render_camera)
{
	UniformBufferObject ubo = {};

	ubo.model = translate(glm::mat4(1.0f), object_transform.get_position().get_glm_vector());
	ubo.model = scale(ubo.model, object_transform.get_scale().get_glm_vector());

	ubo.model = rotate(ubo.model, glm::radians(object_transform.get_rotation().get_x()), glm::vec3(1.0f, 0.0f, 0.0f));
	ubo.model = rotate(ubo.model, glm::radians(object_transform.get_rotation().get_y()), glm::vec3(0.0f, 1.0f, 0.0f));
	ubo.model = rotate(ubo.model, glm::radians(object_transform.get_rotation().get_z()), glm::vec3(0.0f, 0.0f, 1.0f));

	ubo.proj = glm::perspective(glm::radians(45.0f),
	                            swap_chain_extent_.width / static_cast<float>(swap_chain_extent_.height),
	                            render_camera->get_camera_min_draw_distance(),
	                            render_camera->get_camera_max_draw_distance());
	ubo.view = lookAt(render_camera->get_camera_location().get_glm_vector(),
	                  (render_camera->get_camera_location() + render_camera->get_camera_front()).get_glm_vector(),
	                  render_camera->get_camera_up().get_glm_vector());
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
