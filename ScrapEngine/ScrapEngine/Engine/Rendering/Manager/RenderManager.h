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
#include <Engine/Rendering/CommandPool/VulkanCommandPool.h>
#include <Engine/Rendering/Buffer/CommandBuffer/VulkanCommandBuffer.h>
#include <Engine/Rendering/Semaphores/VulkanSemaphoresManager.h>
#include <Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>
#include <Engine/Rendering/Texture/ColorResources/VulkanColorResources.h>
#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>
#include <Engine/Rendering/Model/SkyboxInstance/VulkanSkyboxInstance.h>
#include <TaskScheduler.h>
#include <Engine/LogicCore/Manager/LogicManager.h>

namespace ScrapEngine
{
	namespace Render
	{
		class RenderManager
		{
		private:
			GameWindow* game_window_ = nullptr;
			VukanInstance* vulkan_instance_ = nullptr;
			VulkanDevice* vulkan_render_device_ = nullptr;
			VulkanSwapChain* vulkan_render_swap_chain_ = nullptr;
			VulkanImageView* vulkan_render_image_view_ = nullptr;
			VulkanRenderPass* vulkan_rendering_pass_ = nullptr;
			VulkanFrameBuffer* vulkan_render_frame_buffer_ = nullptr;
			VulkanCommandPool* vulkan_render_command_pool_ = nullptr;
			BaseQueue* vulkan_graphics_queue_ = nullptr;
			BaseQueue* vulkan_presentation_queue_ = nullptr;
			VulkanSemaphoresManager* vulkan_render_semaphores_ = nullptr;
			VulkanSurface* vulkan_window_surface_ = nullptr;
			VulkanDepthResources* vulkan_render_depth_ = nullptr;
			VulkanColorResources* vulkan_render_color_ = nullptr;

			VulkanImGui* gui_render_ = nullptr;

			Camera* render_camera_ = nullptr;
			Camera* default_camera_ = nullptr;

			VulkanSkyboxInstance* skybox_ = nullptr;

			std::vector<VulkanMeshInstance*> loaded_models_;

			size_t current_frame_ = 0;
			uint32_t image_index_;
			vk::Result result_;

			unsigned short int max_frames_in_flight_ = 2;
			bool framebuffer_resized_ = false;
			const std::vector<vk::Semaphore>* image_available_semaphores_ref_;
			const std::vector<vk::Semaphore>* render_finished_semaphores_ref_;
			const std::vector<vk::Fence>* in_flight_fences_ref_;

			//Scheduler tasks
			enki::TaskScheduler g_TS;

			//Multi threaded command buffers
			struct threaded_command_buffer
			{
				bool is_running = false;
				VulkanCommandPool* command_pool = nullptr;
				VulkanCommandBuffer* command_buffer = nullptr;
			};
			//Flag to know if i'm using the first or the second command buffer
			bool command_buffer_flip_flop_ = false;
			std::vector<threaded_command_buffer> command_buffers_;

			//Parallel task used to create command buffer in background
			struct ParallelCommandBufferCreation : enki::ITaskSet
			{
				bool flip_flop = false;
				RenderManager* owner;
				void ExecuteRange(enki::TaskSetPartition range, uint32_t threadnum) override;
			};

			//I need to have a reference to know if is running or is done
			//I need to use a pointer because a ITaskSet cannot be copied
			std::vector<ParallelCommandBufferCreation*> command_buffers_tasks_;
			//This is the fence used to wait that the previous command buffer has finished and can be deleted
			const vk::Fence* waiting_fence_ = nullptr;
		public:
			RenderManager(const game_base_info* received_base_game_info);
			~RenderManager();
			void prepare_to_draw_frame();
			void init_gui_reference(Core::LogicManager* logic_manager) const;
		private:
			void initialize_vulkan(const game_base_info* received_base_game_info);
			void initialize_scheduler();
			void initialize_gui(float width, float height);
			void initialize_command_buffers();

			void create_queues();
			void delete_queues() const;

			void create_command_buffer(bool flip_flop);
			void check_start_new_thread();
			void swap_command_buffers();
			void delete_command_buffers() const;

			void cleanup_swap_chain();
			void recreate_swap_chain();

			void create_camera();
		public:
			void draw_frame();
			void wait_device_idle() const;

			//3D mesh and scene stuff
			VulkanMeshInstance* load_mesh(const std::string& vertex_shader_path,
			                              const std::string& fragment_shader_path,
			                              const std::string& model_path,
			                              const std::vector<std::string>& textures_path);
			VulkanMeshInstance* load_mesh(const std::string& model_path,
			                              const std::vector<std::string>& textures_path);
			void unload_mesh(VulkanMeshInstance* mesh_to_unload);
			VulkanSkyboxInstance* load_skybox(const std::array<std::string, 6>& files_path);

			//User-Window stuff
			GameWindow* get_game_window() const;

			//View-Camera stuff
			Camera* get_render_camera() const;
			Camera* get_default_render_camera() const;
			void set_render_camera(Camera* new_camera);
		};
	}
}
