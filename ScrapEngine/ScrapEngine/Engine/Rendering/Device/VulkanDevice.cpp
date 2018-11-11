#include "VulkanDevice.h"

#include <vector>
#include <map>
#include <set>
#include <algorithm>

//Init Static Members

const vk::Device* ScrapEngine::VulkanDevice::StaticLogicDeviceRef = nullptr;
const vk::PhysicalDevice* ScrapEngine::VulkanDevice::StaticPhysicalDeviceRef = nullptr;

//Class

ScrapEngine::VulkanDevice::VulkanDevice(vk::Instance* VulkanInstanceInputRef, vk::SurfaceKHR* VulkanSurfaceInputRef)
	: instanceRef(VulkanInstanceInputRef), VulkanSurfaceRef(VulkanSurfaceInputRef)
{
	choosePhysicalDevice();
	createLogicalDevice();

	ScrapEngine::VulkanDevice::StaticLogicDeviceRef = &device;
	ScrapEngine::VulkanDevice::StaticPhysicalDeviceRef = &physicalDevice;
}

ScrapEngine::VulkanDevice::~VulkanDevice()
{
	device.destroy();
}

void ScrapEngine::VulkanDevice::choosePhysicalDevice()
{
	uint32_t deviceCount = 0;
	instanceRef->enumeratePhysicalDevices(&deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("VulkanDevice: Failed to find GPUs with Vulkan support!");
	}

	std::vector<vk::PhysicalDevice> devices(deviceCount);
	instanceRef->enumeratePhysicalDevices(&deviceCount, devices.data());

	for (auto& entry_device : devices) {
		if (isDeviceSuitable(&entry_device, VulkanSurfaceRef)) {
			physicalDevice = entry_device;
			msaaSamples = getMaxUsableSampleCount();
			break;
		}
	}

	if (!physicalDevice) {
		throw std::runtime_error("VulkanDevice: Failed to find a suitable GPU!");
	}
}

void ScrapEngine::VulkanDevice::createLogicalDevice()
{
	cached_indices = findQueueFamilies(&physicalDevice, VulkanSurfaceRef);

	std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> uniqueQueueFamilies = { cached_indices.graphicsFamily, cached_indices.presentFamily };

	float queuePriority = 1.0f;
	for (int queueFamily : uniqueQueueFamilies) {
		vk::DeviceQueueCreateInfo queueCreateInfo(
			vk::DeviceQueueCreateFlags(), 
			queueFamily, 
			1, 
			&queuePriority
		);
		queueCreateInfos.push_back(queueCreateInfo);
	}

	vk::PhysicalDeviceFeatures deviceFeatures;
	deviceFeatures.setSamplerAnisotropy(true);
	deviceFeatures.setSampleRateShading(true);

	vk::DeviceCreateInfo createInfo(
		vk::DeviceCreateFlags(),
		static_cast<uint32_t>(queueCreateInfos.size()), 
		queueCreateInfos.data(), 
		0, nullptr, 
		static_cast<uint32_t>(deviceExtensions.size()), deviceExtensions.data(), 
		&deviceFeatures
	);

	if (physicalDevice.createDevice(&createInfo, nullptr, &device) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanDevice: Failed to create logical device!");
	}
}

vk::PhysicalDevice* ScrapEngine::VulkanDevice::getPhysicalDevice()
{
	return &physicalDevice;
}

vk::Device* ScrapEngine::VulkanDevice::getLogicalDevice()
{
	return &device;
}

ScrapEngine::GraphicsQueue::QueueFamilyIndices ScrapEngine::VulkanDevice::getCachedQueueFamilyIndices() const
{
	return cached_indices;
}

bool ScrapEngine::VulkanDevice::isDeviceSuitable(vk::PhysicalDevice* physical_device_input, vk::SurfaceKHR* surface) {
	vk::PhysicalDeviceProperties deviceProperties = physical_device_input->getProperties();
	vk::PhysicalDeviceFeatures deviceFeatures = physical_device_input->getFeatures();

	std::string gpu_name(deviceProperties.deviceName);
	DebugLog::printToConsoleLog("GPU Selected:" + gpu_name);

	GraphicsQueue::QueueFamilyIndices cached_indices = findQueueFamilies(physical_device_input, surface);

	vk::PhysicalDeviceFeatures supportedFeatures = physical_device_input->getFeatures();

	bool extensionsSupported = checkDeviceExtensionSupport(physical_device_input);

	bool swapChainAdequate = false;
	if (extensionsSupported) {
		ScrapEngine::VulkanSwapChain::SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physical_device_input);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	return deviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu && deviceFeatures.geometryShader
		&& cached_indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

bool ScrapEngine::VulkanDevice::checkDeviceExtensionSupport(vk::PhysicalDevice* device)
{
	uint32_t extensionCount;
	device->enumerateDeviceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<vk::ExtensionProperties> availableExtensions(extensionCount);
	device->enumerateDeviceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

ScrapEngine::VulkanSwapChain::SwapChainSupportDetails ScrapEngine::VulkanDevice::querySwapChainSupport(vk::PhysicalDevice* physical_device_input)
{
	ScrapEngine::VulkanSwapChain::SwapChainSupportDetails details;

	physical_device_input->getSurfaceCapabilitiesKHR(*VulkanSurfaceRef, &details.capabilities);

	uint32_t formatCount;
	physical_device_input->getSurfaceFormatsKHR(*VulkanSurfaceRef, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		physical_device_input->getSurfaceFormatsKHR(*VulkanSurfaceRef, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	physical_device_input->getSurfacePresentModesKHR(*VulkanSurfaceRef, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		physical_device_input->getSurfacePresentModesKHR(*VulkanSurfaceRef, &presentModeCount, details.presentModes.data());
	}

	return details;
}

vk::SampleCountFlagBits ScrapEngine::VulkanDevice::getMaxUsableSampleCount()
{
	vk::PhysicalDeviceProperties physicalDeviceProperties = physicalDevice.getProperties();

	vk::SampleCountFlags counts;
	if (
		static_cast<uint32_t>(physicalDeviceProperties.limits.framebufferColorSampleCounts) <
		static_cast<uint32_t>(physicalDeviceProperties.limits.framebufferDepthSampleCounts)
	) {
		counts = physicalDeviceProperties.limits.framebufferColorSampleCounts;
	}
	else {
		counts = physicalDeviceProperties.limits.framebufferDepthSampleCounts;
	}

	if (counts & vk::SampleCountFlagBits::e64) { return vk::SampleCountFlagBits::e64; }
	if (counts & vk::SampleCountFlagBits::e32) { return vk::SampleCountFlagBits::e32; }
	if (counts & vk::SampleCountFlagBits::e16) { return vk::SampleCountFlagBits::e16; }
	if (counts & vk::SampleCountFlagBits::e8) { return vk::SampleCountFlagBits::e8; }
	if (counts & vk::SampleCountFlagBits::e4) { return vk::SampleCountFlagBits::e4; }
	if (counts & vk::SampleCountFlagBits::e2) { return vk::SampleCountFlagBits::e2; }

	return vk::SampleCountFlagBits::e1;
}

vk::SampleCountFlagBits ScrapEngine::VulkanDevice::getMsaaSamples() const
{
	return msaaSamples;
}

ScrapEngine::GraphicsQueue::QueueFamilyIndices ScrapEngine::VulkanDevice::findQueueFamilies(vk::PhysicalDevice* device, vk::SurfaceKHR* surface)
{
	GraphicsQueue::QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	device->getQueueFamilyProperties(&queueFamilyCount, nullptr);

	std::vector<vk::QueueFamilyProperties> queueFamilies(queueFamilyCount);
	device->getQueueFamilyProperties(&queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
			indices.graphicsFamily = i;
		}

		VkBool32 presentSupport = false;
		device->getSurfaceSupportKHR(i, *surface, &presentSupport);

		if (queueFamily.queueCount > 0 && presentSupport) {
			indices.presentFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}
