#include <Engine/Rendering/Buffer/UniformBuffer/ShadowmappingUniformBuffer/DebugQuadUniformBuffer.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/Memory/VulkanMemoryAllocator.h>

ScrapEngine::Render::DebugQuadUniformBuffer::DebugQuadUniformBuffer(const size_t swap_chain_images_size)
{
	const vk::DeviceSize buffer_size(sizeof(UniformBufferObject));

	swap_chain_images_size_ = swap_chain_images_size;
	uniform_buffers_.resize(swap_chain_images_size_);
	uniform_buffers_memory_.resize(swap_chain_images_size_);

	for (size_t i = 0; i < swap_chain_images_size_; i++)
	{
		VulkanMemoryAllocator::get_instance()->create_uniform_buffer(buffer_size, uniform_buffers_[i],
		                                                             uniform_buffers_memory_[i]);
	}

	//Map memory
	mapped_memory_.resize(swap_chain_images_size_);
	for (size_t i = 0; i < swap_chain_images_size_; i++)
	{
		VulkanMemoryAllocator::get_instance()->map_buffer_allocation(uniform_buffers_memory_[i], &mapped_memory_[i]);
	}
}

void ScrapEngine::Render::DebugQuadUniformBuffer::update_uniform_buffer(const uint32_t& current_image,
                                                                        Camera* render_camera)
{
	const float aspect_ratio = render_camera->get_camera_aspect_ratio();

	ubo_debug_quad_.proj = glm::ortho(2.5f / aspect_ratio, 0.0f, 0.0f, 2.5f, -1.0f, 1.0f);
	//Invert image for openGL style
	ubo_debug_quad_.proj[1][1] *= -1;
	
	ubo_debug_quad_.model = glm::mat4(1.0f);

	std::memcpy(mapped_memory_[current_image], &ubo_debug_quad_, sizeof(ubo_debug_quad_));
}
