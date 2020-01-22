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
