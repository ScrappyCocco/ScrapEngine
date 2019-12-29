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
			std::vector<vk::ValidationFeatureEnableEXT> get_enabled_features() const;
			vk::DispatchLoaderDynamic* get_dynamic_dispatcher();
			
		private:
			vk::DispatchLoaderDynamic dispatcher_;

			vk::DebugUtilsMessengerEXT callback_;

			//Callback function that display the messages
			static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
				VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
				VkDebugUtilsMessageTypeFlagsEXT message_type,
				const VkDebugUtilsMessengerCallbackDataEXT* p_callback_data,
				void* p_user_data);

			//---------------------------------------------------
			//CONFIG VARS
			//YOU CAN DISABLE/ENABLE VALIDATION LAYERS OR OTHER STUFF FROM HERE

			//List of validationLayers to load and use
			const std::vector<const char*> validation_layers_ = {
				"VK_LAYER_KHRONOS_validation"
			};
			
			//List of additional features to be used
			const std::vector<vk::ValidationFeatureEnableEXT> enabled_features_ = {
				vk::ValidationFeatureEnableEXT::eBestPractices
			};
			
			//If you want to see all infos messages
			static const bool enable_info_messages = false;

			//This automatically disable them on Release mode on VS
			//Modify it if you want them permanently disabled or enabled
#ifdef NDEBUG
			static const bool enable_validation_layers = false;
#else
			static const bool enable_validation_layers = true;
#endif
		};
	}
}
