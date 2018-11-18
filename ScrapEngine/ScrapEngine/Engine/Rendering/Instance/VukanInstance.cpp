#include "VukanInstance.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//Init Static Members

const vk::Instance* ScrapEngine::VukanInstance::StaticInstanceRef = nullptr;

//Class

ScrapEngine::VukanInstance::VukanInstance(const std::string& app_name, int app_version, const std::string& engine_name, int engine_version)
{
	if (VulkanValidationLayers::areValidationLayersEnabled()) {
		ValidationLayersManager = new VulkanValidationLayers();
	}

	createVulkanInstance(app_name, app_version, engine_name, engine_version);
	StaticInstanceRef = &instance;

	if (ValidationLayersManager) {
		ValidationLayersManager->setupDebugCallback();
	}
}

ScrapEngine::VukanInstance::~VukanInstance()
{
	if (ValidationLayersManager) {
		delete ValidationLayersManager;
	}
	vkDestroyInstance(instance, nullptr);
}

void ScrapEngine::VukanInstance::createVulkanInstance(std::string app_name, int app_version, std::string engine_name, int engine_version)
{
	vk::ApplicationInfo appInfo(app_name.c_str(), app_version, engine_name.c_str(), engine_version, VK_API_VERSION_1_0);

	auto extensions = getRequiredExtensions();

	vk::InstanceCreateInfo createInfo(
		vk::InstanceCreateFlags(), 
		&appInfo, 
		0, 
		nullptr, 
		static_cast<uint32_t>(extensions.size()), 
		extensions.data()
	);

	std::vector<const char*> layers;
	if (ValidationLayersManager) {
		layers = ValidationLayersManager->getValidationLayers();
		createInfo.setEnabledLayerCount(static_cast<uint32_t>(layers.size()));
		createInfo.setPpEnabledLayerNames(layers.data());
	}

	if (vk::createInstance(&createInfo, nullptr, &instance) != vk::Result::eSuccess) {
		throw std::runtime_error("VukanInstance: Failed to create instance!");
	}
}

vk::Instance* ScrapEngine::VukanInstance::getVulkanInstance()
{
	return &instance;
}

std::vector<const char*> ScrapEngine::VukanInstance::getRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (ValidationLayersManager) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}
