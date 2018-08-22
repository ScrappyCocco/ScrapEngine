#include "VukanInstance.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

ScrapEngine::VukanInstance::VukanInstance(std::string app_name, int app_version, std::string engine_name, int engine_version)
{
	createVulkanInstance(app_name, app_version, engine_name, engine_version);
}

ScrapEngine::VukanInstance::~VukanInstance()
{
	vkDestroyInstance(instance, nullptr);
}

void ScrapEngine::VukanInstance::createVulkanInstance(std::string app_name, int app_version, std::string engine_name, int engine_version)
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = app_name.c_str();
	appInfo.applicationVersion = VK_MAKE_VERSION(app_version, 0, 0);
	appInfo.pEngineName = engine_name.c_str();
	appInfo.engineVersion = VK_MAKE_VERSION(engine_version, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}

VkInstance ScrapEngine::VukanInstance::getVulkanInstance() const
{
	return instance;
}

std::vector<const char*> ScrapEngine::VukanInstance::getRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	return extensions;
}
