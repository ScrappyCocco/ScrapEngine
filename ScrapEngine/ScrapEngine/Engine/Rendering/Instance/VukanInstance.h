#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <Engine/Rendering/ValidationLayers/VulkanValidationLayers.h>
#include <string>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class VukanInstance
		{
		private:
			//Singleton static instance
			static VukanInstance* instance_;

			/**
			 * \brief Vulkan Instance of the engine - connection between the application and the Vulkan library
			 */
			vk::Instance vulkan_instance_;

			//Reference to ValidationLayersManager that display vulkan warning/errors
			VulkanValidationLayers* validation_layers_manager_ = nullptr;

			//The constructor is private because this class is a Singleton
			VukanInstance() = default;
		public:
			//Method used to init the class with parameters because the constructor is private
			void init(const std::string& app_name,
			          int app_version,
			          const std::string& engine_name = "ScrapEngine",
			          int engine_version = 1);

			//Destroy the Vulkan Instance
			~VukanInstance();

			//Singleton static function to get or create a class instance
			static VukanInstance* get_instance();

			//Create the Vulkan Instance with the given data
			void create_vulkan_instance(const std::string& app_name,
			                            int app_version,
			                            const std::string& engine_name = "ScrapEngine",
			                            int engine_version = 1);

			//Return the current Vulkan Instance (if created)
			vk::Instance* get_vulkan_instance();
			//Conversion operators
			operator VkInstance();
			operator vk::Instance() const;

			//Return the validation layers manager (useful to create the device)
			VulkanValidationLayers* get_validation_layers_manager() const;
		private:
			std::vector<const char*> get_required_extensions() const;
		};
	}
}
