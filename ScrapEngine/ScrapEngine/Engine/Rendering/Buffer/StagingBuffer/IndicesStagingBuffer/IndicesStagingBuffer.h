#pragma once

#include <Engine/Rendering/Buffer/StagingBuffer/BaseStagingBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class IndicesStagingBuffer : public BaseStagingBuffer
		{
		public:
			IndicesStagingBuffer(const vk::DeviceSize& buffer_size, const std::vector<uint32_t>* vector_data);

			~IndicesStagingBuffer() = default;
		};
	}
}
