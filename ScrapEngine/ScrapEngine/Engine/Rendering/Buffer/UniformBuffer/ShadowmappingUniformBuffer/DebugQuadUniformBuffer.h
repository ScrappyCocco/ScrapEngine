#pragma once

#include <Engine/Rendering/Buffer/UniformBuffer/BaseUniformBuffer.h>
#include <Engine/Rendering/Camera/Camera.h>

namespace ScrapEngine
{
	namespace Render
	{
		struct OffscreenDebugQuadUniformBufferObject
		{
			glm::mat4 projection;
			glm::mat4 model;
		};
		
		class DebugQuadUniformBuffer : public BaseUniformBuffer
		{
		private:
			size_t swap_chain_images_size_;

			OffscreenDebugQuadUniformBufferObject ubo_debug_quad_ = {};
		public:
			DebugQuadUniformBuffer(size_t swap_chain_images_size);
			~DebugQuadUniformBuffer() = default;

			void update_uniform_buffer(const uint32_t& current_image, Camera* render_camera);
		};
	}
}
