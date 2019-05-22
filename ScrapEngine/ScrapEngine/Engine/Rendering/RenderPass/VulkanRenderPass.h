#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanRenderPass
		{
		private:
			//Singleton static instance
			vk::RenderPass render_pass_;

			static VulkanRenderPass* instance_;

			//The constructor is private because this class is a Singleton
			VulkanRenderPass() = default;
		public:
			//Method used to init the class with parameters because the constructor is private
			void init(const vk::Format& swap_chain_image_format, vk::SampleCountFlagBits msaa_samples);

			~VulkanRenderPass();

			static VulkanRenderPass* get_instance();

			//Singleton static function to get or create a class instance
			vk::RenderPass* get_render_pass();
		};
	}
}
