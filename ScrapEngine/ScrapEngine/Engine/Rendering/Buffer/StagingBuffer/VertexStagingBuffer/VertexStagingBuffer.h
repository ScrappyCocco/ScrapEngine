#pragma once

#include <vulkan/vulkan.hpp>
#include <Engine/Rendering/Buffer/StagingBuffer/BaseStagingBuffer.h>
#include <Engine/Rendering/Base/Vertex.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VertexStagingBuffer : public BaseStagingBuffer
		{
		public:
			VertexStagingBuffer(const vk::DeviceSize& buffer_size, const std::vector<Vertex>* vector_data);

			~VertexStagingBuffer() = default;
		};
	}
}
