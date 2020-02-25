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

		struct SkyboxUniformBufferObject
		{
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 proj;
		};

		class SkyboxUniformBuffer : public BaseUniformBuffer
		{
		private:
			SkyboxUniformBufferObject ubo_ = {};
		public:
			SkyboxUniformBuffer(size_t swap_chain_images_size);
			~SkyboxUniformBuffer() = default;

			void update_uniform_buffer_transform(const Core::STransform& object_transform);
			void update_uniform_buffer_camera_data(Camera* render_camera);
			void finish_update_uniform_buffer(uint32_t current_image) override;
		};
	}
}
