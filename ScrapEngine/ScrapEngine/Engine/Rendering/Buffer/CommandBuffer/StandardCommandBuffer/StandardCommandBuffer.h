#pragma once

#include <Engine/Rendering/Buffer/CommandBuffer/BaseCommandBuffer.h>
#include <Engine/Rendering/Buffer/FrameBuffer/BaseFrameBuffer.h>
#include <Engine/Rendering/Model/SkyboxInstance/VulkanSkyboxInstance.h>
#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>
#include <Engine/Rendering/CommandPool/VulkanCommandPool.h>
#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardCommandBuffer : public BaseCommandBuffer
		{
		private:
			Camera* current_camera_ = nullptr;

			void pre_shadow_mesh_commands(StandardShadowmapping* shadowmapping);

			//This is the sphere radius multiplier that will be used to check if a mesh is in the camera frustum
			//Shadow frustum check double this value to avoid (possibly) to remove objects that still have the shadow visible
			const float frustum_sphere_radius_multiplier_ = 7.5f;
		public:
			explicit StandardCommandBuffer(VulkanCommandPool* command_pool, int16_t cb_size);

			~StandardCommandBuffer() = default;

			void init_shadow_map(StandardShadowmapping* shadowmapping);
			void load_mesh_shadow_map(StandardShadowmapping* shadowmapping,
			                          VulkanMeshInstance* mesh);

			void init_command_buffer(vk::Extent2D* input_swap_chain_extent_ref,
			                         BaseFrameBuffer* swap_chain_frame_buffer);
			void init_current_camera(Camera* current_camera);

			void load_skybox(VulkanSkyboxInstance* skybox_ref);
			void load_mesh(VulkanMeshInstance* mesh);
		};
	}
}
