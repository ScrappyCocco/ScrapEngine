#include "VulkanDevice.h"

#include <vector>
#include <set>
#include "../../Debug/DebugLog.h"

//Init Static Members

const vk::Device* ScrapEngine::Render::VulkanDevice::static_logic_device_ref = nullptr;
const vk::PhysicalDevice* ScrapEngine::Render::VulkanDevice::static_physical_device_ref = nullptr;

//Class

ScrapEngine::Render::VulkanDevice::VulkanDevice(vk::Instance* vulkan_instance_input_ref,
                                                vk::SurfaceKHR* vulkan_surface_input_ref)
	: instance_ref_(vulkan_instance_input_ref), vulkan_surface_ref_(vulkan_surface_input_ref)
{
	choose_physical_device();
	create_logical_device();

	static_logic_device_ref = &device_;
	static_physical_device_ref = &physical_device_;
}

ScrapEngine::Render::VulkanDevice::~VulkanDevice()
{
	device_.destroy();
}

void ScrapEngine::Render::VulkanDevice::choose_physical_device()
{
	uint32_t device_count = 0;
	instance_ref_->enumeratePhysicalDevices(&device_count, nullptr);

	if (device_count == 0)
	{
		throw std::runtime_error("VulkanDevice: Failed to find GPUs with Vulkan support!");
	}

	std::vector<vk::PhysicalDevice> devices(device_count);
	instance_ref_->enumeratePhysicalDevices(&device_count, devices.data());

	for (auto& entry_device : devices)
	{
		if (is_device_suitable(&entry_device, vulkan_surface_ref_))
		{
			physical_device_ = entry_device;
			msaa_samples_ = get_max_usable_sample_count();
			break;
		}
	}

	if (!physical_device_)
	{
		throw std::runtime_error("VulkanDevice: Failed to find a suitable GPU!");
	}
}

void ScrapEngine::Render::VulkanDevice::create_logical_device()
{
	cached_indices_ = find_queue_families(&physical_device_, vulkan_surface_ref_);

	std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> unique_queue_families = {cached_indices_.graphicsFamily, cached_indices_.presentFamily};

	float queuePriority = 1.0f;
	for (int queue_family : unique_queue_families)
	{
		vk::DeviceQueueCreateInfo queueCreateInfo(
			vk::DeviceQueueCreateFlags(),
			queue_family,
			1,
			&queuePriority
		);
		queueCreateInfos.push_back(queueCreateInfo);
	}

	vk::PhysicalDeviceFeatures device_features;
	device_features.setSamplerAnisotropy(true);
	device_features.setSampleRateShading(true);

	vk::DeviceCreateInfo create_info(
		vk::DeviceCreateFlags(),
		static_cast<uint32_t>(queueCreateInfos.size()),
		queueCreateInfos.data(),
		0, nullptr,
		static_cast<uint32_t>(device_extensions_.size()), device_extensions_.data(),
		&device_features
	);

	if (physical_device_.createDevice(&create_info, nullptr, &device_) != vk::Result::eSuccess)
	{
		throw std::runtime_error("VulkanDevice: Failed to create logical device!");
	}
}

vk::PhysicalDevice* ScrapEngine::Render::VulkanDevice::get_physical_device()
{
	return &physical_device_;
}

vk::Device* ScrapEngine::Render::VulkanDevice::get_logical_device()
{
	return &device_;
}

ScrapEngine::Render::GraphicsQueue::QueueFamilyIndices ScrapEngine::Render::VulkanDevice::
get_cached_queue_family_indices() const
{
	return cached_indices_;
}

bool ScrapEngine::Render::VulkanDevice::is_device_suitable(vk::PhysicalDevice* physical_device_input,
                                                           vk::SurfaceKHR* surface)
{
	vk::PhysicalDeviceProperties deviceProperties = physical_device_input->getProperties();
	vk::PhysicalDeviceFeatures deviceFeatures = physical_device_input->getFeatures();

	std::string gpu_name(deviceProperties.deviceName);
	Debug::DebugLog::print_to_console_log("GPU Selected:" + gpu_name);

	GraphicsQueue::QueueFamilyIndices cached_indices = find_queue_families(physical_device_input, surface);

	vk::PhysicalDeviceFeatures supported_features = physical_device_input->getFeatures();

	bool extensions_supported = check_device_extension_support(physical_device_input);

	bool swap_chain_adequate = false;
	if (extensions_supported)
	{
		ScrapEngine::Render::VulkanSwapChain::SwapChainSupportDetails swap_chain_support = query_swap_chain_support(
			physical_device_input);
		swap_chain_adequate = !swap_chain_support.formats.empty() && !swap_chain_support.presentModes.empty();
	}

	return deviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu && deviceFeatures.geometryShader
		&& cached_indices.isComplete() && extensions_supported && swap_chain_adequate && supported_features.
		samplerAnisotropy;
}

bool ScrapEngine::Render::VulkanDevice::check_device_extension_support(vk::PhysicalDevice* device) const
{
	uint32_t extension_count;
	device->enumerateDeviceExtensionProperties(nullptr, &extension_count, nullptr);

	std::vector<vk::ExtensionProperties> availableExtensions(extension_count);
	device->enumerateDeviceExtensionProperties(nullptr, &extension_count, availableExtensions.data());

	std::set<std::string> requiredExtensions(device_extensions_.begin(), device_extensions_.end());

	for (const auto& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

ScrapEngine::Render::VulkanSwapChain::SwapChainSupportDetails ScrapEngine::Render::VulkanDevice::
query_swap_chain_support(vk::PhysicalDevice* physical_device_input) const
{
	ScrapEngine::Render::VulkanSwapChain::SwapChainSupportDetails details;

	physical_device_input->getSurfaceCapabilitiesKHR(*vulkan_surface_ref_, &details.capabilities);

	uint32_t format_count;
	physical_device_input->getSurfaceFormatsKHR(*vulkan_surface_ref_, &format_count, nullptr);

	if (format_count != 0)
	{
		details.formats.resize(format_count);
		physical_device_input->getSurfaceFormatsKHR(*vulkan_surface_ref_, &format_count, details.formats.data());
	}

	uint32_t presentModeCount;
	physical_device_input->getSurfacePresentModesKHR(*vulkan_surface_ref_, &presentModeCount, nullptr);

	if (presentModeCount != 0)
	{
		details.presentModes.resize(presentModeCount);
		physical_device_input->getSurfacePresentModesKHR(*vulkan_surface_ref_, &presentModeCount,
		                                                 details.presentModes.data());
	}

	return details;
}

vk::SampleCountFlagBits ScrapEngine::Render::VulkanDevice::get_max_usable_sample_count() const
{
	const vk::PhysicalDeviceProperties physical_device_properties = physical_device_.getProperties();

	vk::SampleCountFlags counts;
	if (
		static_cast<uint32_t>(physical_device_properties.limits.framebufferColorSampleCounts) <
		static_cast<uint32_t>(physical_device_properties.limits.framebufferDepthSampleCounts)
	)
	{
		counts = physical_device_properties.limits.framebufferColorSampleCounts;
	}
	else
	{
		counts = physical_device_properties.limits.framebufferDepthSampleCounts;
	}

	if (counts & vk::SampleCountFlagBits::e64) { return vk::SampleCountFlagBits::e64; }
	if (counts & vk::SampleCountFlagBits::e32) { return vk::SampleCountFlagBits::e32; }
	if (counts & vk::SampleCountFlagBits::e16) { return vk::SampleCountFlagBits::e16; }
	if (counts & vk::SampleCountFlagBits::e8) { return vk::SampleCountFlagBits::e8; }
	if (counts & vk::SampleCountFlagBits::e4) { return vk::SampleCountFlagBits::e4; }
	if (counts & vk::SampleCountFlagBits::e2) { return vk::SampleCountFlagBits::e2; }

	return vk::SampleCountFlagBits::e1;
}

vk::SampleCountFlagBits ScrapEngine::Render::VulkanDevice::get_msaa_samples() const
{
	return msaa_samples_;
}

ScrapEngine::Render::GraphicsQueue::QueueFamilyIndices ScrapEngine::Render::VulkanDevice::find_queue_families(
	vk::PhysicalDevice* physical_device_input, vk::SurfaceKHR* surface)
{
	GraphicsQueue::QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	physical_device_input->getQueueFamilyProperties(&queueFamilyCount, nullptr);

	std::vector<vk::QueueFamilyProperties> queueFamilies(queueFamilyCount);
	physical_device_input->getQueueFamilyProperties(&queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queue_family : queueFamilies)
	{
		if (queue_family.queueCount > 0 && queue_family.queueFlags & vk::QueueFlagBits::eGraphics)
		{
			indices.graphicsFamily = i;
		}

		VkBool32 present_support = false;
		physical_device_input->getSurfaceSupportKHR(i, *surface, &present_support);

		if (queue_family.queueCount > 0 && present_support)
		{
			indices.presentFamily = i;
		}

		if (indices.isComplete())
		{
			break;
		}

		i++;
	}

	return indices;
}
