#include <Engine/Rendering/Semaphores/VulkanSemaphoresManager.h>

#include <stdexcept>
#include "Engine/Rendering/Device/VulkanDevice.h"

ScrapEngine::Render::VulkanSemaphoresManager::VulkanSemaphoresManager(
	const unsigned short int input_max_frames_in_flight)
	: MAX_FRAMES_IN_FLIGHT(input_max_frames_in_flight)
{
	image_available_semaphores_.resize(MAX_FRAMES_IN_FLIGHT);
	render_finished_semaphores_.resize(MAX_FRAMES_IN_FLIGHT);
	in_flight_fences_.resize(MAX_FRAMES_IN_FLIGHT);

	vk::SemaphoreCreateInfo semaphore_info;

	vk::FenceCreateInfo fence_info(vk::FenceCreateFlagBits::eSignaled);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		if (VulkanDevice::get_instance()->get_logical_device()->createSemaphore(&semaphore_info, nullptr,
		                                                                        &image_available_semaphores_[i])
			!= vk::Result::eSuccess ||
			VulkanDevice::get_instance()->get_logical_device()->createSemaphore(&semaphore_info, nullptr,
			                                                                    &render_finished_semaphores_[i])
			!= vk::Result::eSuccess ||
			VulkanDevice::get_instance()->get_logical_device()->createFence(&fence_info, nullptr, &in_flight_fences_[i])
			!= vk::Result::eSuccess)
		{
			throw std::runtime_error("Failed to create VulkanSemaphoresManager for a frame!");
		}
	}
}

ScrapEngine::Render::VulkanSemaphoresManager::~VulkanSemaphoresManager()
{
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		VulkanDevice::get_instance()->get_logical_device()->destroySemaphore(render_finished_semaphores_[i]);
		VulkanDevice::get_instance()->get_logical_device()->destroySemaphore(image_available_semaphores_[i]);
		VulkanDevice::get_instance()->get_logical_device()->destroyFence(in_flight_fences_[i]);
	}
}

int ScrapEngine::Render::VulkanSemaphoresManager::getMaxFramesInFlight() const
{
	return MAX_FRAMES_IN_FLIGHT;
}

const std::vector<vk::Semaphore>* ScrapEngine::Render::VulkanSemaphoresManager::
get_image_available_semaphores_vector() const
{
	return &image_available_semaphores_;
}

const std::vector<vk::Semaphore>* ScrapEngine::Render::VulkanSemaphoresManager::
get_render_finished_semaphores_vector() const
{
	return &render_finished_semaphores_;
}

const std::vector<vk::Fence>* ScrapEngine::Render::VulkanSemaphoresManager::get_in_flight_fences_vector() const
{
	return &in_flight_fences_;
}
