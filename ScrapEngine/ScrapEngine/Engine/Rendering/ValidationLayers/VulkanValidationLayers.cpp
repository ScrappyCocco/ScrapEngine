#include "VulkanValidationLayers.h"
#include "../../Debug/DebugLog.h"
#include "../Base/StaticTypes.h"

ScrapEngine::Render::VulkanValidationLayers::VulkanValidationLayers()
{
	if (enableValidationLayers && !checkValidationLayerSupport()) {
		throw std::runtime_error("VulkanValidationLayers: validation layers requested, but not available!");
	}
}

ScrapEngine::Render::VulkanValidationLayers::~VulkanValidationLayers()
{
	VukanInstance::StaticInstanceRef->destroyDebugUtilsMessengerEXT(callback, nullptr, dispatcher);
}

void ScrapEngine::Render::VulkanValidationLayers::setupDebugCallback()
{
	if (!enableValidationLayers) return;

	vk::DebugUtilsMessengerCreateInfoEXT createInfo(
		vk::DebugUtilsMessengerCreateFlagsEXT(),
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
		, vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
		debugCallback
	);

	dispatcher.init(*VukanInstance::StaticInstanceRef);

	callback = VukanInstance::StaticInstanceRef->createDebugUtilsMessengerEXT(createInfo, nullptr, dispatcher);

	Debug::DebugLog::print_to_console_log("VulkanValidationLayers: VulkanValidationLayers ENABLED!");
}

bool ScrapEngine::Render::VulkanValidationLayers::checkValidationLayerSupport()
{
	uint32_t layerCount;
	vk::enumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<vk::LayerProperties> availableLayers(layerCount);
	vk::enumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

bool ScrapEngine::Render::VulkanValidationLayers::areValidationLayersEnabled()
{
	return enableValidationLayers;
}

std::vector<const char*> ScrapEngine::Render::VulkanValidationLayers::getValidationLayers()
{
	return validationLayers;
}

VKAPI_ATTR VkBool32 VKAPI_CALL ScrapEngine::Render::VulkanValidationLayers::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData)
{
	std::string messageSeverityString;
	switch (messageSeverity) {
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: //the most verbose output indicating all diagnostic messages from the Vulkan loader, layers, and drivers should be captured.
		messageSeverityString = "[VulkanValidationLayers VERBOSE Message]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: //specifies an informational message such as resource details that may be handy when debugging an application.
		messageSeverityString = "[VulkanValidationLayers INFO Message]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: //specifies use of Vulkan that may expose an app bug
		messageSeverityString = "[VulkanValidationLayers WARNING Message]";
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: //specifies that an error that may cause undefined results, including an application crash.
		messageSeverityString = "[VulkanValidationLayers ERROR Message]";
		break;
	default:
		messageSeverityString = "[VulkanValidationLayers Generic Message]";
		break;
	}

	Debug::DebugLog::print_exception_to_console_log(messageSeverityString, pCallbackData->pMessage);

	return VK_FALSE;
}

