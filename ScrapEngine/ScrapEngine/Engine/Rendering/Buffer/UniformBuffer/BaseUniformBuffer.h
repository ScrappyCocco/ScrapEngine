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

			const std::vector<vk::Buffer>* get_uniform_buffers() const;
		};
	}
}
