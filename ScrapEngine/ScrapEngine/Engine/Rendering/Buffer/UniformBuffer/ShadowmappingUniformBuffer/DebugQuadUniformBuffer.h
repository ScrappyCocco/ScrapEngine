#pragma once

#include <Engine/Rendering/Buffer/UniformBuffer/BaseUniformBuffer.h>
#include <Engine/Rendering/Camera/Camera.h>
#include <Engine/Rendering/Buffer/UniformBuffer/StandardUniformBuffer/StandardUniformBuffer.h>

namespace ScrapEngine
{
	namespace Render
	{
		class DebugQuadUniformBuffer : public BaseUniformBuffer
		{
		private:
			size_t swap_chain_images_size_;

			UniformBufferObject ubo_debug_quad_ = {};
		public:
			DebugQuadUniformBuffer(size_t swap_chain_images_size);
			~DebugQuadUniformBuffer() = default;

			void update_uniform_buffer(const uint32_t& current_image, Camera* render_camera);
		};
	}
}
