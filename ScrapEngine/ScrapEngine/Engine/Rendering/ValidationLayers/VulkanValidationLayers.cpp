#include <Engine/Rendering/ValidationLayers/VulkanValidationLayers.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Instance/VukanInstance.h>

ScrapEngine::Render::VulkanValidationLayers::VulkanValidationLayers()
{
	if (enable_validation_layers && !check_validation_layer_support())
	{
		Debug::DebugLog::fatal_error(vk::Result(-13), "VulkanValidationLayers: validation layers requested, but not available!");
	}
}

ScrapEngine::Render::VulkanValidationLayers::~VulkanValidationLayers()
{
	VukanInstance::get_instance()->get_vulkan_instance()->
	                               destroyDebugUtilsMessengerEXT(callback_, nullptr, dispatcher_);
}

void ScrapEngine::Render::VulkanValidationLayers::setup_debug_callback()
{
	if (!enable_validation_layers) return;

	Debug::DebugLog::print_to_console_log("Loading VulkanValidationLayers...");

	vk::DebugUtilsMessengerCreateInfoEXT create_info(
		vk::DebugUtilsMessengerCreateFlagsEXT(),
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
		vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
		vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
		debug_callback
	);

	if (enable_info_messages)
	{
		create_info.setMessageSeverity(create_info.messageSeverity | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo);
	}

	const vk::DynamicLoader dl;
	const PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
		dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");

	dispatcher_ = vk::DispatchLoaderDynamic(*VukanInstance::get_instance(), vkGetInstanceProcAddr);

	callback_ = VukanInstance::get_instance()->get_vulkan_instance()->createDebugUtilsMessengerEXT(
		create_info, nullptr, dispatcher_);

	Debug::DebugLog::print_to_console_log("VulkanValidationLayers: VulkanValidationLayers ENABLED!");
}

bool ScrapEngine::Render::VulkanValidationLayers::check_validation_layer_support() const
{
	std::vector<vk::LayerProperties> available_layers = vk::enumerateInstanceLayerProperties();

	for (const char* layer_name : validation_layers_)
	{
		bool layer_found = false;

		for (const auto& layer_properties : available_layers)
		{
			if (strcmp(layer_name, layer_properties.layerName) == 0)
			{
				layer_found = true;
				break;
			}
		}

		if (!layer_found)
		{
			Debug::DebugLog::print_to_console_log(
				"VulkanValidationLayers: Unable to load layer: " + std::string(layer_name));
			return false;
		}
	}

	return true;
}

bool ScrapEngine::Render::VulkanValidationLayers::are_validation_layers_enabled()
{
	return enable_validation_layers;
}

std::vector<const char*> ScrapEngine::Render::VulkanValidationLayers::get_validation_layers() const
{
	return validation_layers_;
}

std::vector<vk::ValidationFeatureEnableEXT> ScrapEngine::Render::VulkanValidationLayers::get_enabled_features() const
{
	return enabled_features_;
}

vk::DispatchLoaderDynamic* ScrapEngine::Render::VulkanValidationLayers::get_dynamic_dispatcher()
{
	return &dispatcher_;
}

VKAPI_ATTR VkBool32 VKAPI_CALL ScrapEngine::Render::VulkanValidationLayers::debug_callback(
	const VkDebugUtilsMessageSeverityFlagBitsEXT message_severity, VkDebugUtilsMessageTypeFlagsEXT message_type,
	const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data, void* p_user_data)
{
	std::string message_severity_string;
	switch (message_severity)
	{
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		//the most verbose output indicating all diagnostic messages from the Vulkan loader, layers, and drivers should be captured.
		message_severity_string = "[VulkanValidationLayers-Callback][VERBOSE]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		//specifies an informational message such as resource details that may be handy when debugging an application.
		message_severity_string = "[VulkanValidationLayers-Callback][INFO]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: //specifies use of Vulkan that may expose an app bug
		message_severity_string = "[VulkanValidationLayers-Callback][WARNING]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		//specifies that an error that may cause undefined results, including an application crash.
		message_severity_string = "[VulkanValidationLayers-Callback][ERROR]";
		break;
	default:
		message_severity_string = "[VulkanValidationLayers-Callback][Generic]";
		break;
	}

	Debug::DebugLog::print_exception_to_console_log(message_severity_string, p_callback_data->pMessage);

	return VK_FALSE;
}
