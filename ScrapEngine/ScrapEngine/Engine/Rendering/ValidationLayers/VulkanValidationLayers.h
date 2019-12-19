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
			vk::DispatchLoaderDynamic dispatcher_;

			//List of validationLayers to load and use
			const std::vector<const char*> validation_layers_ = {
				"VK_LAYER_LUNARG_standard_validation"
			};

			vk::DebugUtilsMessengerEXT callback_;

			//Callback function that display the messages
			static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
				VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
				VkDebugUtilsMessageTypeFlagsEXT message_type,
				const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
				void* p_user_data);

#ifdef NDEBUG
			static const bool enable_validation_layers = false;
#else
			static const bool enable_validation_layers = true;
#endif
		};
	}
}
