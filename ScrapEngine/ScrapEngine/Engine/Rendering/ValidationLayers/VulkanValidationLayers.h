#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine {

	class VulkanValidationLayers
	{
	public:
		VulkanValidationLayers();
		~VulkanValidationLayers();

		void setupDebugCallback(vk::Instance* instance);
		bool checkValidationLayerSupport();
		static bool areValidationLayersEnabled();
		std::vector<const char*> getValidationLayers();

	private:
		vk::Instance* instanceRef;
		vk::DispatchLoaderDynamic dispatcher;

		//List of validationLayers to load and use
		const std::vector<const char*> validationLayers = {
			"VK_LAYER_LUNARG_standard_validation"
		};

		vk::DebugUtilsMessengerEXT callback;

		//Callback function that display the messages
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

#ifdef NDEBUG
		static const bool enableValidationLayers = false;
#else
		static const bool enableValidationLayers = true;
#endif
	};
}

