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
		class Camera;

		struct UniformBufferObject
		{
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 proj;
			glm::mat4 depth_bias_mvp;
			glm::vec3 light_pos;
		};

		class StandardUniformBuffer : public BaseUniformBuffer
		{
		private:
			//Used to force update of camera matrices the first time
			//Otherwise an object created at runtime will see matrices not dirty
			bool first_update_ = true;

			size_t swap_chain_images_size_;

			UniformBufferObject ubo_ = {};
		public:
			StandardUniformBuffer(size_t swap_chain_images_size);
			~StandardUniformBuffer() = default;

			void update_uniform_buffer(const uint32_t& current_image, const Core::STransform& object_transform,
			                           Camera* render_camera, const glm::vec3& light_pos, const glm::mat4& depth_bias_m,
			                           bool update_transform = true);
		};
	}
}
