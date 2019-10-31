#include <Engine/Rendering/Device/VulkanDevice.h>
#include <vector>
#include <set>
#include <Engine/Debug/DebugLog.h>

//Init static instance reference

ScrapEngine::Render::VulkanDevice* ScrapEngine::Render::VulkanDevice::instance_ = nullptr;

void ScrapEngine::Render::VulkanDevice::init(vk::Instance* vulkan_instance_input_ref,
                                             vk::SurfaceKHR* vulkan_surface_input_ref)
{
	instance_ref_ = vulkan_instance_input_ref;
	vulkan_surface_ref_ = vulkan_surface_input_ref;

	choose_physical_device();
	create_logical_device();
}

ScrapEngine::Render::VulkanDevice::~VulkanDevice()
{
	device_.destroy();
}

ScrapEngine::Render::VulkanDevice* ScrapEngine::Render::VulkanDevice::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VulkanDevice();
	}
	return instance_;
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

	std::vector<vk::DeviceQueueCreateInfo> queue_create_infos;
	const std::set<int> unique_queue_families = {cached_indices_.graphics_family, cached_indices_.present_family};

	float queue_priority = 1.0f;
	for (int queue_family : unique_queue_families)
	{
		vk::DeviceQueueCreateInfo queue_create_info(
			vk::DeviceQueueCreateFlags(),
			queue_family,
			1,
			&queue_priority
		);
		queue_create_infos.push_back(queue_create_info);
	}

	vk::PhysicalDeviceFeatures device_features;
	device_features.setSamplerAnisotropy(true);
	device_features.setSampleRateShading(true);

	const vk::DeviceCreateInfo create_info(
		vk::DeviceCreateFlags(),
		static_cast<uint32_t>(queue_create_infos.size()),
		queue_create_infos.data(),
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

ScrapEngine::Render::BaseQueue::QueueFamilyIndices ScrapEngine::Render::VulkanDevice::
get_cached_queue_family_indices() const
{
	return cached_indices_;
}

bool ScrapEngine::Render::VulkanDevice::is_device_suitable(vk::PhysicalDevice* physical_device_input,
                                                           vk::SurfaceKHR* surface)
{
	const vk::PhysicalDeviceProperties device_properties = physical_device_input->getProperties();
	const vk::PhysicalDeviceFeatures device_features = physical_device_input->getFeatures();

	std::string gpu_name(device_properties.deviceName);
	Debug::DebugLog::print_to_console_log("GPU Selected:" + gpu_name);
	Debug::DebugLog::print_to_console_log("GPU API v" + std::to_string(device_properties.apiVersion));
	Debug::DebugLog::print_to_console_log("GPU Driver v" + std::to_string(device_properties.driverVersion));

	BaseQueue::QueueFamilyIndices cached_indices = find_queue_families(physical_device_input, surface);

	const vk::PhysicalDeviceFeatures supported_features = physical_device_input->getFeatures();

	bool extensions_supported = check_device_extension_support(physical_device_input);

	bool swap_chain_adequate = false;
	if (extensions_supported)
	{
		VulkanSwapChain::SwapChainSupportDetails swap_chain_support = query_swap_chain_support(
			physical_device_input);
		swap_chain_adequate = !swap_chain_support.formats.empty() && !swap_chain_support.present_modes.empty();
	}

	return device_properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu && device_features.geometryShader
		&& cached_indices.is_complete() && extensions_supported && swap_chain_adequate && supported_features.
		samplerAnisotropy;
}

bool ScrapEngine::Render::VulkanDevice::check_device_extension_support(vk::PhysicalDevice* device) const
{
	uint32_t extension_count;
	device->enumerateDeviceExtensionProperties(nullptr, &extension_count, nullptr);

	std::vector<vk::ExtensionProperties> available_extensions(extension_count);
	device->enumerateDeviceExtensionProperties(nullptr, &extension_count, available_extensions.data());

	std::set<std::string> required_extensions(device_extensions_.begin(), device_extensions_.end());

	for (const auto& extension : available_extensions)
	{
		required_extensions.erase(extension.extensionName);
	}

	return required_extensions.empty();
}

ScrapEngine::Render::VulkanSwapChain::SwapChainSupportDetails ScrapEngine::Render::VulkanDevice::
query_swap_chain_support(vk::PhysicalDevice* physical_device_input) const
{
	VulkanSwapChain::SwapChainSupportDetails details;

	physical_device_input->getSurfaceCapabilitiesKHR(*vulkan_surface_ref_, &details.capabilities);

	uint32_t format_count;
	physical_device_input->getSurfaceFormatsKHR(*vulkan_surface_ref_, &format_count, nullptr);

	if (format_count != 0)
	{
		details.formats.resize(format_count);
		physical_device_input->getSurfaceFormatsKHR(*vulkan_surface_ref_, &format_count, details.formats.data());
	}

	uint32_t present_mode_count;
	physical_device_input->getSurfacePresentModesKHR(*vulkan_surface_ref_, &present_mode_count, nullptr);

	if (present_mode_count != 0)
	{
		details.present_modes.resize(present_mode_count);
		physical_device_input->getSurfacePresentModesKHR(*vulkan_surface_ref_, &present_mode_count,
		                                                 details.present_modes.data());
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

ScrapEngine::Render::BaseQueue::QueueFamilyIndices ScrapEngine::Render::VulkanDevice::find_queue_families(
	vk::PhysicalDevice* physical_device_input, vk::SurfaceKHR* surface)
{
	BaseQueue::QueueFamilyIndices indices;

	uint32_t queue_family_count = 0;
	physical_device_input->getQueueFamilyProperties(&queue_family_count, nullptr);

	std::vector<vk::QueueFamilyProperties> queue_families(queue_family_count);
	physical_device_input->getQueueFamilyProperties(&queue_family_count, queue_families.data());

	int i = 0;
	for (const auto& queue_family : queue_families)
	{
		if (queue_family.queueCount > 0 && queue_family.queueFlags & vk::QueueFlagBits::eGraphics)
		{
			indices.graphics_family = i;
		}

		VkBool32 present_support = false;
		physical_device_input->getSurfaceSupportKHR(i, *surface, &present_support);

		if (queue_family.queueCount > 0 && present_support)
		{
			indices.present_family = i;
		}

		if (indices.is_complete())
		{
			break;
		}

		i++;
	}

	return indices;
}
