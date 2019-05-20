#pragma once

#include <Engine/Utility/UsefulTypes.h>
#include <Engine/Rendering/Window/GameWindow.h>
#include <Engine/Rendering/Window/VulkanSurface.h>
#include <Engine/Rendering/Instance/VukanInstance.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/SwapChain/VulkanImageView.h>
#include <Engine/Rendering/RenderPass/VulkanRenderPass.h>
#include <Engine/Rendering/Buffer/FrameBuffer/VulkanFrameBuffer.h>
#include <Engine/Rendering/Command/VulkanCommandPool.h>
#include <Engine/Rendering/Buffer/CommandBuffer/VulkanCommandBuffer.h>
#include <Engine/Rendering/Semaphores/VulkanSemaphoresManager.h>
#include <Engine/Rendering/Queue/GraphicsQueue.h>
#include <Engine/Rendering/Queue/PresentQueue.h>
#include <Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h>
#include <Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>
#include <Engine/Rendering/Texture/VulkanColorResources.h>
#include <Engine/Rendering/Model/VulkanMeshInstance.h>
#include <Engine/Rendering/Model/VulkanSkyboxInstance.h>

namespace ScrapEngine
{
	namespace Render
	{
		class RenderManager
		{
		private:
			ScrapEngine::Render::GameWindow* game_window_ = nullptr;
			ScrapEngine::Render::VukanInstance* vulkan_instance_ = nullptr;
			ScrapEngine::Render::VulkanDevice* vulkan_render_device_ = nullptr;
			ScrapEngine::Render::VulkanSwapChain* vulkan_render_swap_chain_ = nullptr;
			ScrapEngine::Render::VulkanImageView* vulkan_render_image_view_ = nullptr;
			ScrapEngine::Render::VulkanRenderPass* vulkan_rendering_pass_ = nullptr;
			ScrapEngine::Render::VulkanFrameBuffer* vulkan_render_frame_buffer_ = nullptr;
			ScrapEngine::Render::VulkanCommandPool* vulkan_render_command_pool_ = nullptr;
			ScrapEngine::Render::VulkanCommandBuffer* vulkan_render_command_buffer_ = nullptr;
			ScrapEngine::Render::GraphicsQueue* vulkan_graphics_queue_ = nullptr;
			ScrapEngine::Render::PresentQueue* vulkan_presentation_queue_ = nullptr;
			ScrapEngine::Render::VulkanSemaphoresManager* vulkan_render_semaphores_ = nullptr;
			ScrapEngine::Render::VulkanSurface* vulkan_window_surface_ = nullptr;
			ScrapEngine::Render::VulkanDepthResources* vulkan_render_depth_ = nullptr;
			ScrapEngine::Render::VulkanColorResources* vulkan_render_color_ = nullptr;

			ScrapEngine::Render::Camera* render_camera_ = nullptr;
			ScrapEngine::Render::Camera* default_camera_ = nullptr;

			ScrapEngine::Render::VulkanSkyboxInstance* skybox_ = nullptr;

			std::vector<ScrapEngine::Render::VulkanMeshInstance*> loaded_models_;

			size_t current_frame_ = 0;
			uint32_t image_index_;
			vk::Result result_;

			unsigned short int max_frames_in_flight_ = 2;
			bool framebuffer_resized_ = false;
			const std::vector<vk::Semaphore>* image_available_semaphores_ref_;
			const std::vector<vk::Semaphore>* render_finished_semaphores_ref_;
			const std::vector<vk::Fence>* in_flight_fences_ref_;
		public:
			RenderManager(const ScrapEngine::game_base_info* received_base_game_info);
			~RenderManager();
		private:
			auto initialize_vulkan(const ScrapEngine::game_base_info* received_base_game_info) -> void;

			void create_queues();
			void delete_queues() const;

			void create_command_buffers();
			void delete_command_buffers() const;

			void cleanup_swap_chain();
			void recreate_swap_chain();

			void create_camera();
		public:
			void draw_frame();
			void wait_device_idle() const;

			//3D mesh and scene stuff
			ScrapEngine::Render::VulkanMeshInstance* load_mesh(const std::string& vertex_shader_path,
			                                                   const std::string& fragment_shader_path,
			                                                   const std::string& model_path,
			                                                   const std::vector<std::string>& textures_path);
			ScrapEngine::Render::VulkanMeshInstance* load_mesh(const std::string& model_path,
			                                                   const std::vector<std::string>& textures_pathh);
			void unload_mesh(ScrapEngine::Render::VulkanMeshInstance* mesh_to_unload);
			ScrapEngine::Render::VulkanSkyboxInstance* load_skybox(const std::array<std::string, 6>& files_path);

			//User-Window stuff
			ScrapEngine::Render::GameWindow* get_game_window() const;

			//View-Camera stuff
			ScrapEngine::Render::Camera* get_render_camera() const;
			ScrapEngine::Render::Camera* get_default_render_camera() const;
			void set_render_camera(ScrapEngine::Render::Camera* new_camera);
		};
	}
}
