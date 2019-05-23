#pragma once
#include <unordered_map>
#include <Engine/Rendering/Model/Model/VulkanModel.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanModelPool
		{
		private:
			//Singleton static instance
			static VulkanModelPool* instance_;

			//The constructor is private because this class is a Singleton
			VulkanModelPool() = default;

			std::unordered_map<std::string, std::shared_ptr<VulkanModel>> model_pool_;
		public:
			//Singleton static function to get or create a class instance
			static VulkanModelPool* get_instance();

			std::shared_ptr<VulkanModel> get_model(const std::string& model_path);

			~VulkanModelPool();

			void clear_memory();
		};
	}
}
