#include <Engine/Rendering/Buffer/UniformBuffer/StandardUniformBuffer/StandardUniformBuffer.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <glm/gtx/quaternion.hpp>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>
#include <Engine/Rendering/Camera/Camera.h>

ScrapEngine::Render::StandardUniformBuffer::StandardUniformBuffer(const size_t swap_chain_images_size)
{
	const vk::DeviceSize buffer_size(sizeof(UniformBufferObject));

	uniform_buffers_.resize(swap_chain_images_size);
	uniform_buffers_memory_.resize(swap_chain_images_size);

	for (size_t i = 0; i < swap_chain_images_size; i++)
	{
		VulkanMemoryAllocator::get_instance()->create_uniform_buffer(buffer_size, uniform_buffers_[i],
		                                                             uniform_buffers_memory_[i]);
	}

	//Map memory
	mapped_memory_.resize(swap_chain_images_size);
	for (size_t i = 0; i < swap_chain_images_size; i++)
	{
		VulkanMemoryAllocator::get_instance()->map_buffer_allocation(uniform_buffers_memory_[i], &mapped_memory_[i]);
	}
}

void ScrapEngine::Render::StandardUniformBuffer::update_uniform_buffer_transform(
	const Core::STransform& object_transform)
{
	//Traslate
	ubo_.model = translate(glm::mat4(1.0f), object_transform.get_position().get_glm_vector());

	//Rotate
	const glm::mat4 rotation_matrix = toMat4(object_transform.get_quat_rotation().get_glm_quat());
	ubo_.model = ubo_.model * rotation_matrix;

	//Scale
	ubo_.model = scale(ubo_.model, object_transform.get_scale().get_glm_vector());
}

void ScrapEngine::Render::StandardUniformBuffer::update_uniform_buffer_camera_data(Camera* render_camera)
{
	//Perspective and look stuff
	ubo_.proj = render_camera->get_camera_projection_matrix();
	ubo_.view = render_camera->get_camera_look_matrix();
}

void ScrapEngine::Render::StandardUniformBuffer::update_uniform_buffer_light_data(const glm::vec3& light_pos,
                                                                                  const glm::mat4& depth_bias_m)
{
	ubo_.light_pos = light_pos;
	ubo_.depth_bias_mvp = depth_bias_m;
}

void ScrapEngine::Render::StandardUniformBuffer::finish_update_uniform_buffer(const uint32_t current_image)
{
	std::memcpy(mapped_memory_[current_image], &ubo_, sizeof(ubo_));
}
