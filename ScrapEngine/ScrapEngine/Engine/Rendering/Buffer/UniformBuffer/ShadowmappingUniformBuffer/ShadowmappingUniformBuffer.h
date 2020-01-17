#pragma once

#include <Engine/Rendering/Buffer/UniformBuffer/BaseUniformBuffer.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>
#include <glm/mat4x4.hpp>

namespace ScrapEngine
{
	namespace Render
	{
		struct OffscreenUniformBufferObject
		{
			glm::mat4 depth_mvp;
		};

		class ShadowmappingUniformBuffer : public BaseUniformBuffer
		{
		private:
			size_t swap_chain_images_size_;

			OffscreenUniformBufferObject offscreen_ubo_ = {};
		public:
			ShadowmappingUniformBuffer(size_t swap_chain_images_size);
			~ShadowmappingUniformBuffer() = default;

			void update_uniform_buffer(const uint32_t& current_image, float light_fov, const glm::vec3& light_pos, float z_near, float z_far);

			glm::mat4 get_depth_bias() const;
		};
	}
}
