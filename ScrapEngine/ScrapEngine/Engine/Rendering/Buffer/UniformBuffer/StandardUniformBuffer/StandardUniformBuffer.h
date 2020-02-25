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
			UniformBufferObject ubo_ = {};
		public:
			StandardUniformBuffer(size_t swap_chain_images_size);
			~StandardUniformBuffer() = default;

			void update_uniform_buffer_transform(const Core::STransform& object_transform);
			void update_uniform_buffer_camera_data(Camera* render_camera);
			void update_uniform_buffer_light_data(const glm::vec3& light_pos, const glm::mat4& depth_bias_m);
			void finish_update_uniform_buffer(uint32_t current_image) override;
		};
	}
}
