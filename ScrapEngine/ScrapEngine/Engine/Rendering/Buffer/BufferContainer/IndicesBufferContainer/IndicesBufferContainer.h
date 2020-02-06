#pragma once

#include <Engine/Rendering/Buffer/BufferContainer/BufferContainer.h>
#include <vector>

namespace ScrapEngine
{
	namespace Render
	{
		class IndicesBufferContainer : public BufferContainer
		{
		private:
			const std::vector<uint32_t>* indices_;
		public:
			IndicesBufferContainer(vk::Buffer* input_buffer, const std::vector<uint32_t>* input_indices);
			~IndicesBufferContainer() = default;

			const std::vector<uint32_t>* get_vector() const;
		};
	}
}
