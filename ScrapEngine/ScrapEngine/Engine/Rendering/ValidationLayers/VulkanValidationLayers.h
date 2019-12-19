#pragma once

#include <Engine/Rendering/VulkanInclude.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanValidationLayers
		{
		public:
			VulkanValidationLayers();
			~VulkanValidationLayers();

			void setup_debug_callback();
			bool check_validation_layer_support() const;
			static bool are_validation_layers_enabled();
			std::vector<const char*> get_validation_layers() const;

		private:
			VkDebugUtilsMessengerEXT callback;

			//List of validationLayers to load and use
			const std::vector<const char*> validation_layers_ = {
				"VK_LAYER_LUNARG_standard_validation"
			};

			//Callback function that display the messages
			static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
				VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
				VkDebugUtilsMessageTypeFlagsEXT message_type,
				const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
				void* p_user_data);

			//From https://github.com/bwasty/vulkan-tutorial-hpp/blob/master/steps/02_validation_layers.cpp
			VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
				const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
				const VkAllocationCallbacks* pAllocator,
				VkDebugUtilsMessengerEXT* pCallback);
			void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback,
				const VkAllocationCallbacks* pAllocator);

#ifdef NDEBUG
			static const bool enable_validation_layers = false;
#else
			static const bool enable_validation_layers = true;
#endif
		};
	}
}
