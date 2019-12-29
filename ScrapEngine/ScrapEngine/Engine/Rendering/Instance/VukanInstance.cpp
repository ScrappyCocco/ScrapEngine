#include <Engine/Rendering/Instance/VukanInstance.h>

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

//Init static instance reference

ScrapEngine::Render::VukanInstance* ScrapEngine::Render::VukanInstance::instance_ = nullptr;

//Class

void ScrapEngine::Render::VukanInstance::init(const std::string& app_name,
                                              const int app_version,
                                              const std::string& engine_name,
                                              const int engine_version)
{
	if (VulkanValidationLayers::are_validation_layers_enabled())
	{
		validation_layers_manager_ = new VulkanValidationLayers();
	}

	create_vulkan_instance(app_name, app_version, engine_name, engine_version);

	if (validation_layers_manager_)
	{
		validation_layers_manager_->setup_debug_callback();
	}
}

ScrapEngine::Render::VukanInstance::~VukanInstance()
{
	delete validation_layers_manager_;

	vkDestroyInstance(vulkan_instance_, nullptr);
}

ScrapEngine::Render::VukanInstance* ScrapEngine::Render::VukanInstance::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VukanInstance();
	}
	return instance_;
}

void ScrapEngine::Render::VukanInstance::create_vulkan_instance(const std::string& app_name,
                                                                const int app_version,
                                                                const std::string& engine_name,
                                                                const int engine_version)
{
	vk::ApplicationInfo app_info(app_name.c_str(), app_version, engine_name.c_str(), engine_version,
	                             VK_API_VERSION_1_1);

	std::vector<const char*> extensions = get_required_extensions();

	vk::InstanceCreateInfo create_info(
		vk::InstanceCreateFlags(),
		&app_info,
		0,
		nullptr,
		static_cast<uint32_t>(extensions.size()),
		extensions.data()
	);

	std::vector<const char*> layers;
	vk::ValidationFeaturesEXT additional_features;
	std::vector<vk::ValidationFeatureEnableEXT> additional_featues_list;
	if (validation_layers_manager_)
	{
		//Load enabled layers
		layers = validation_layers_manager_->get_validation_layers();
		create_info.setEnabledLayerCount(static_cast<uint32_t>(layers.size()));
		create_info.setPpEnabledLayerNames(layers.data());

		//Load enabled additional features
		additional_featues_list = validation_layers_manager_->get_enabled_features();
		additional_features.setEnabledValidationFeatureCount(static_cast<uint32_t>(additional_featues_list.size()));
		additional_features.setPEnabledValidationFeatures(additional_featues_list.data());
		create_info.setPNext(&additional_features);
	}

	if (vk::createInstance(&create_info, nullptr, &vulkan_instance_) != vk::Result::eSuccess)
	{
		throw std::runtime_error("VukanInstance: Failed to create instance!");
	}
}

vk::Instance* ScrapEngine::Render::VukanInstance::get_vulkan_instance()
{
	return &vulkan_instance_;
}

ScrapEngine::Render::VukanInstance::operator VkInstance_T*()
{
	return *get_vulkan_instance();
}

ScrapEngine::Render::VulkanValidationLayers* ScrapEngine::Render::VukanInstance::get_validation_layers_manager() const
{
	return validation_layers_manager_;
}

std::vector<const char*> ScrapEngine::Render::VukanInstance::get_required_extensions() const
{
	uint32_t glfw_extension_count = 0;
	const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

	std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_count);

	if (validation_layers_manager_)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		extensions.push_back(VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME);
	}

	return extensions;
}
