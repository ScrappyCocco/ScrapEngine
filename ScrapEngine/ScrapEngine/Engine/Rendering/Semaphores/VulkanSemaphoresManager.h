#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanSemaphoresManager
		{
		private:
			std::vector<vk::Semaphore> image_available_semaphores_;
			std::vector<vk::Semaphore> render_finished_semaphores_;
			std::vector<vk::Fence> in_flight_fences_;

			uint32_t image_count_ = -1;
		public:
			VulkanSemaphoresManager(uint32_t input_image_count);
			~VulkanSemaphoresManager();

			const std::vector<vk::Semaphore>* get_image_available_semaphores_vector() const;
			const std::vector<vk::Semaphore>* get_render_finished_semaphores_vector() const;
			const std::vector<vk::Fence>* get_in_flight_fences_vector() const;
		};
	}
}
