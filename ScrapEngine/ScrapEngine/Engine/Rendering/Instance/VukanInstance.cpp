#include "VukanInstance.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//Init Static Members

const vk::Instance* ScrapEngine::Render::VukanInstance::static_instance_ref = nullptr;

//Class

ScrapEngine::Render::VukanInstance::VukanInstance(const std::string& app_name, int app_version, const std::string& engine_name, int engine_version)
{
	if (VulkanValidationLayers::areValidationLayersEnabled()) {
		validation_layers_manager_ = new VulkanValidationLayers();
	}

	create_vulkan_instance(app_name, app_version, engine_name, engine_version);
	static_instance_ref = &instance_;

	if (validation_layers_manager_) {
		validation_layers_manager_->setupDebugCallback();
	}
}

ScrapEngine::Render::VukanInstance::~VukanInstance()
{
	delete validation_layers_manager_;

	vkDestroyInstance(instance_, nullptr);
}

void ScrapEngine::Render::VukanInstance::create_vulkan_instance(std::string app_name, int app_version, std::string engine_name, int engine_version)
{
	vk::ApplicationInfo app_info(app_name.c_str(), app_version, engine_name.c_str(), engine_version, VK_API_VERSION_1_0);

	auto extensions = get_required_extensions();

	vk::InstanceCreateInfo create_info(
		vk::InstanceCreateFlags(), 
		&app_info, 
		0, 
		nullptr, 
		static_cast<uint32_t>(extensions.size()), 
		extensions.data()
	);

	std::vector<const char*> layers;
	if (validation_layers_manager_) {
		layers = validation_layers_manager_->getValidationLayers();
		create_info.setEnabledLayerCount(static_cast<uint32_t>(layers.size()));
		create_info.setPpEnabledLayerNames(layers.data());
	}

	if (vk::createInstance(&create_info, nullptr, &instance_) != vk::Result::eSuccess) {
		throw std::runtime_error("VukanInstance: Failed to create instance!");
	}
}

vk::Instance* ScrapEngine::Render::VukanInstance::get_vulkan_instance()
{
	return &instance_;
}

std::vector<const char*> ScrapEngine::Render::VukanInstance::get_required_extensions() const
{
	uint32_t glfwExtensionCount = 0;
	const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfwExtensionCount);

	if (validation_layers_manager_) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}
