#pragma once

#include <Engine/Rendering/RenderPass/BaseRenderPass.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardRenderPass : public BaseRenderPass
		{
		private:
			//Singleton static instance
			static StandardRenderPass* instance_;

			//The constructor is private because this class is a Singleton
			StandardRenderPass() = default;

			vk::SampleCountFlagBits msaa_samples_;
		public:
			//Method used to init the class with parameters because the constructor is private
			void init(const vk::Format& swap_chain_image_format, vk::SampleCountFlagBits msaa_samples);

			~StandardRenderPass() = default;

			static StandardRenderPass* get_instance();

			vk::SampleCountFlagBits get_msaa_samples() const;
		};
	}
}
