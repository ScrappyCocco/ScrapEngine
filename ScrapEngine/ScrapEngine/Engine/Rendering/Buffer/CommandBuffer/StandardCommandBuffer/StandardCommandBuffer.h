#pragma once

#include <Engine/Rendering/Buffer/CommandBuffer/BaseCommandBuffer.h>
#include <Engine/Rendering/Buffer/FrameBuffer/VulkanFrameBuffer.h>
#include <Engine/Rendering/Model/SkyboxInstance/VulkanSkyboxInstance.h>
#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>
#include <Engine/Rendering/CommandPool/VulkanCommandPool.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardCommandBuffer : public BaseCommandBuffer
		{
		private:
			Camera* current_camera_ = nullptr;
		public:
			StandardCommandBuffer() = default;

			~StandardCommandBuffer() = default;

			void init_command_buffer(VulkanFrameBuffer* swap_chain_frame_buffer,
			                         vk::Extent2D* input_swap_chain_extent_ref,
			                         VulkanCommandPool* command_pool);
			void init_current_camera(Camera* current_camera);

			void load_skybox(VulkanSkyboxInstance* skybox_ref);
			void load_mesh(VulkanMeshInstance* mesh);
		};
	}
}
