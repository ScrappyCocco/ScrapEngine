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
			//Used to force update of camera matrices the first time
			//Otherwise an object created at runtime will see matrices not dirty
			bool first_update_ = true;

			size_t swap_chain_images_size_;

			SkyboxUniformBufferObject ubo_ = {};
		public:
			SkyboxUniformBuffer(size_t swap_chain_images_size);
			~SkyboxUniformBuffer() = default;

			void update_uniform_buffer(const uint32_t& current_image, const Core::STransform& object_transform,
			                           Camera* render_camera, bool update_transform = true);
		};
	}
}
