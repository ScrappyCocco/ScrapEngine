#include <Engine/Rendering/Buffer/FrameBuffer/BaseFrameBuffer.h>
#include <Engine/Rendering/Device/VulkanDevice.h>

ScrapEngine::Render::BaseFrameBuffer::~BaseFrameBuffer()
{
	for (auto& framebuffer : framebuffers_)
	{
		VulkanDevice::get_instance()->get_logical_device()->destroyFramebuffer(framebuffer);
	}
}

const std::vector<vk::Framebuffer>* ScrapEngine::Render::BaseFrameBuffer::get_framebuffers_vector() const
{
	return &framebuffers_;
}

size_t ScrapEngine::Render::BaseFrameBuffer::get_framebuffers_vector_size() const
{
	return framebuffers_.size();
}
