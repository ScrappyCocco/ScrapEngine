#pragma once

#include <Engine/Rendering/Buffer/UniformBuffer/BaseUniformBuffer.h>
#include <glm/mat4x4.hpp>

namespace ScrapEngine
{
	namespace Core
	{
		class STransform;
	}
}

namespace ScrapEngine
{
	namespace Render
	{
		struct OffscreenUniformBufferObject
		{
			glm::mat4 model;
			glm::mat4 depth_mvp;
		};

		class ShadowmappingUniformBuffer : public BaseUniformBuffer
		{
		private:
			OffscreenUniformBufferObject offscreen_ubo_ = {};
		public:
			ShadowmappingUniformBuffer(size_t swap_chain_images_size);
			~ShadowmappingUniformBuffer() = default;

			void update_uniform_buffer_transform(const Core::STransform& object_transform);
			void update_uniform_buffer_light(float light_fov, const glm::vec3& light_pos, const glm::vec3& light_lookat,
			                                 float z_near, float z_far);
			void finish_update_uniform_buffer(uint32_t current_image);

			glm::mat4 get_depth_bias() const;
		};
	}
}
