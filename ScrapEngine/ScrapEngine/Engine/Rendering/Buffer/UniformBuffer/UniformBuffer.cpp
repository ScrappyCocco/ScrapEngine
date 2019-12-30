#include <Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Buffer/BaseBuffer.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <glm/gtx/quaternion.hpp>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

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
		VulkanMemoryAllocator::get_instance()->create_uniform_buffer(buffer_size, uniform_buffers_[i], uniform_buffers_memory_[i]);
	}
	
	//Map memory
	mapped_memory_.resize(swap_chain_images_size_);
	for (size_t i = 0; i < swap_chain_images_size_; i++)
	{
		VulkanMemoryAllocator::get_instance()->map_buffer_allocation(uniform_buffers_memory_[i], &mapped_memory_[i]);
	}
}

ScrapEngine::Render::UniformBuffer::~UniformBuffer()
{
	for (size_t i = 0; i < swap_chain_images_size_; i++)
	{
		VulkanMemoryAllocator::get_instance()->unmap_buffer_allocation(uniform_buffers_memory_[i]);
		VulkanMemoryAllocator::get_instance()->destroy_buffer(uniform_buffers_[i], uniform_buffers_memory_[i]);
	}
}

void ScrapEngine::Render::UniformBuffer::update_uniform_buffer(const uint32_t& current_image,
                                                               const Core::STransform& object_transform,
                                                               Camera* render_camera, const bool update_transform)
{
	if (update_transform) {
		//Traslate
		ubo_.model = translate(glm::mat4(1.0f), object_transform.get_position().get_glm_vector());

		//Rotate
		const glm::mat4 rotation_matrix = toMat4(object_transform.get_quat_rotation().get_glm_quat());
		ubo_.model = ubo_.model * rotation_matrix;

		//Scale
		ubo_.model = scale(ubo_.model, object_transform.get_scale().get_glm_vector());
	}

	//Perspective and look stuff
	if (render_camera->get_projection_matrix_dirty() || first_update_) {
		ubo_.proj = render_camera->get_camera_projection_matrix();
	}
	if (render_camera->get_look_matrix_dirt() || first_update_) {
		ubo_.view = render_camera->get_camera_look_matrix();
		first_update_ = false;
	}

	std::memcpy(mapped_memory_[current_image], &ubo_, sizeof(ubo_));
}

const std::vector<vk::Buffer>* ScrapEngine::Render::UniformBuffer::get_uniform_buffers() const
{
	return &uniform_buffers_;
}
