#pragma once

#include <vulkan/vulkan.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		class BufferContainer
		{
		private:
			vk::Buffer* buffer_;
		public:
			BufferContainer(vk::Buffer* input_buffer);
			virtual ~BufferContainer() = 0;

			vk::Buffer* get_buffer() const;
		};
	}
}
