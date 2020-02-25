#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class BaseUniformBuffer
		{
		protected:
			std::vector<vk::Buffer> uniform_buffers_;
			std::vector<VmaAllocation> uniform_buffers_memory_;
			std::vector<void*> mapped_memory_;
		public:
			BaseUniformBuffer() = default;
			virtual ~BaseUniformBuffer() = 0;

			//Call to confirm the uniform buffer update and copy the new data
			virtual void finish_update_uniform_buffer(uint32_t current_image) = 0;

			const std::vector<vk::Buffer>* get_uniform_buffers() const;
		};
	}
}
