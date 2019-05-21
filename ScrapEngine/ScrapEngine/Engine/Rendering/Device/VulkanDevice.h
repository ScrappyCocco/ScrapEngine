#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Instance/VukanInstance.h>
#include <Engine/Rendering/Queue/BaseQueue.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanDevice
		{
		private:
			vk::Instance* instance_ref_;
			vk::SurfaceKHR* vulkan_surface_ref_;

			vk::SampleCountFlagBits msaa_samples_ = vk::SampleCountFlagBits::e1;

			BaseQueue::QueueFamilyIndices cached_indices_;

			vk::PhysicalDevice physical_device_; //physical graphics card
			vk::Device device_; //logical connection to graphics card

			//List of Extensions to check
			const std::vector<const char*> device_extensions_ = {
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};
		public:
			static const vk::Device* static_logic_device_ref;
			static const vk::PhysicalDevice* static_physical_device_ref;

			VulkanDevice(vk::Instance* vulkan_instance_input_ref, vk::SurfaceKHR* vulkan_surface_input_ref);

			//Turn off the logical device
			~VulkanDevice();

			//Choose and assign the best physicalDevice
			void choose_physical_device();

			//Initialize the LogicalDevice
			void create_logical_device();

			//Return a reference to physicalDevice
			vk::PhysicalDevice* get_physical_device();

			//Return a reference to logical device
			vk::Device* get_logical_device();

			BaseQueue::QueueFamilyIndices get_cached_queue_family_indices() const;

			//Which queue families are supported by the device
			BaseQueue::QueueFamilyIndices find_queue_families(
				vk::PhysicalDevice* physical_device_input, vk::SurfaceKHR* surface);

			VulkanSwapChain::SwapChainSupportDetails query_swap_chain_support(vk::PhysicalDevice* physical_device_input) const;

			vk::SampleCountFlagBits get_max_usable_sample_count() const;

			vk::SampleCountFlagBits get_msaa_samples() const;
		private:
			bool is_device_suitable(vk::PhysicalDevice* physical_device_input, vk::SurfaceKHR* surface);

			bool check_device_extension_support(vk::PhysicalDevice* device) const;
		};
	}
}
