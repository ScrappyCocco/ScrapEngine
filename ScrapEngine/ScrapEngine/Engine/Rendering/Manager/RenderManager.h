#pragma once

#include <Engine/Utility/UsefulTypes.h>
#include <Engine/Rendering/Window/GameWindow.h>
#include <Engine/Rendering/Window/VulkanSurface.h>
#include <Engine/Rendering/Instance/VukanInstance.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/SwapChain/VulkanImageView.h>
#include <Engine/Rendering/RenderPass/BaseRenderPass.h>
#include <Engine/Rendering/Buffer/FrameBuffer/VulkanFrameBuffer.h>
#include <Engine/Rendering/CommandPool/VulkanCommandPool.h>
#include <Engine/Rendering/Buffer/CommandBuffer/GuiCommandBuffer/GuiCommandBuffer.h>
#include <Engine/Rendering/Buffer/CommandBuffer/StandardCommandBuffer/StandardCommandBuffer.h>
#include <Engine/Rendering/Semaphores/VulkanSemaphoresManager.h>
#include <Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>
#include <Engine/Rendering/Texture/ColorResources/VulkanColorResources.h>
#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>
#include <Engine/Rendering/Model/SkyboxInstance/VulkanSkyboxInstance.h>
#include <Engine/Rendering/Gui/VulkanImGui.h>
#include <TaskScheduler.h>
#include <list>

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
			VulkanFrameBuffer* vulkan_render_frame_buffer_ = nullptr;
			
			VulkanCommandPool* vulkan_render_command_pool_ = nullptr;
			VulkanCommandPool* command_buffer_command_pool_ = nullptr;
			VulkanCommandPool* gui_buffer_command_pool_ = nullptr;
			
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

			std::list<VulkanMeshInstance*> loaded_models_;

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

			//---standard command buffers
			//Multi threaded command buffers
			struct threaded_command_buffer
			{
				bool is_running = false;
				StandardCommandBuffer* command_buffer = nullptr;
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

			//---gui
			//The gui command buffer, is rebuilt every frame
			GuiCommandBuffer* gui_command_buffer_;
			BaseRenderPass* gui_render_pass_ = nullptr;

			//Parallel task used to create gui command buffer while other updates() execute
			//It's started at post_gui_render() and run during audio and physics update
			//Must be ready before draw frame() or will be waited
			struct ParallelGuiCommandBufferCreation : enki::ITaskSet
			{
				RenderManager* owner;
				void ExecuteRange(enki::TaskSetPartition range, uint32_t threadnum) override;
			};

			ParallelGuiCommandBufferCreation* gui_command_buffer_task_;

			//This is the fence used to wait that the previous command buffer has finished and can be deleted
			const vk::Fence* gui_waiting_fence_ = nullptr;

			//Necessary to rebuild the gui command buffer
			//This because "image_index_" might be updated before the gui thread read it and this will lead to error
			//So this variable is updated only at the end of the frame
			uint32_t last_image_index_ = 0;

			//---cleanup

			//Parallel task used to delete meshes in background while other updates() execute
			//Every mesh has a flag that say if it can be deleted or not
			struct ParallelMeshCleanup : enki::ITaskSet
			{
				RenderManager* owner;
				void ExecuteRange(enki::TaskSetPartition range, uint32_t threadnum) override;
			};

			ParallelMeshCleanup* mesh_cleanup_task_;
		public:
			RenderManager(const game_base_info* received_base_game_info);
			~RenderManager();
		private:
			void initialize_vulkan(const game_base_info* received_base_game_info);
			void initialize_scheduler();
			void initialize_gui(float width, float height);
			void initialize_command_buffers();
			void initialize_gui_command_buffers();

			void create_queues();
			void delete_queues() const;

			void rebuild_gui_command_buffer(bool for_next_image = true) const;

			void wait_cleanup_task();
			void wait_gui_commandbuffer_task();
			void wait_pre_frame_tasks();

			void cleanup_meshes();
			void create_command_buffer(bool flip_flop);
			void check_start_new_thread();
			bool swap_command_buffers();
			void delete_command_buffers() const;

			void cleanup_swap_chain();
			void recreate_swap_chain();

			void create_camera();
		public:
			//Rebuild the command buffer
			//Is better to call this before starting the main loop
			//So there's a command buffer ready to use with all the objects loaded
			void prepare_to_draw_frame();

			//Draw call used to display the loading screen
			//Is not very different from draw_frame, but is used only at startup now
			//Is useful because doesn't call multithreaded tasks
			void draw_loading_frame();

			//Standard draw frame call
			void draw_frame();

			//Wait for the render device to be in idle state
			void wait_device_idle() const;

			//3D mesh and scene stuff
			VulkanMeshInstance* load_mesh(const std::string& vertex_shader_path,
			                              const std::string& fragment_shader_path,
			                              const std::string& model_path,
			                              const std::vector<std::string>& textures_path);
			VulkanMeshInstance* load_mesh(const std::string& model_path,
			                              const std::vector<std::string>& textures_path);
			VulkanSkyboxInstance* load_skybox(const std::array<std::string, 6>& files_path);

			//User-Window stuff
			GameWindow* get_game_window() const;

			//View-Camera stuff
			Camera* get_render_camera() const;
			Camera* get_default_render_camera() const;
			void set_render_camera(Camera* new_camera);

			//Gui stuff
			void pre_gui_render() const;
			void post_gui_render();
		};
	}
}
