#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Queue/GraphicsQueue/GraphicsQueue.h>
#include <Engine/Rendering/Queue/PresentationQueue/PresentQueue.h>
#include <Engine/Rendering/Model/ObjectPool/VulkanModelBuffersPool/VulkanModelBuffersPool.h>
#include <Engine/Rendering/Model/ObjectPool/VulkanModelPool/VulkanModelPool.h>
#include <Engine/Rendering/Model/ObjectPool/VulkanSimpleMaterialPool/VulkanSimpleMaterialPool.h>
#include <Engine/Rendering/CommandPool/Singleton/SingletonCommandPool.h>
#include <Engine/Rendering/CommandPool/Standard/StandardCommandPool.h>

void ScrapEngine::Render::RenderManager::ParallelCommandBufferCreation::ExecuteRange(enki::TaskSetPartition range,
                                                                                     uint32_t threadnum)
{
	if (owner->waiting_fence_)
	{
		const vk::Result result = VulkanDevice::get_instance()->get_logical_device()
		                                                ->waitForFences(1, owner->waiting_fence_, true, 10000);
		if (result == vk::Result::eSuccess) {
			owner->waiting_fence_ = nullptr;
		}else if(result == vk::Result::eTimeout)
		{
			throw std::runtime_error("Fence timeout");
		}else
		{
			throw std::runtime_error("An error occurred while waiting a fence...");
		}
	}
	owner->create_command_buffer(flip_flop);
}

ScrapEngine::Render::RenderManager::RenderManager(const game_base_info* received_base_game_info)
{
	game_window_ = new GameWindow(received_base_game_info->window_width,
	                              received_base_game_info->window_height,
	                              received_base_game_info->app_name);
	Debug::DebugLog::print_to_console_log("GameWindow created");
	initialize_vulkan(received_base_game_info);
	Debug::DebugLog::print_to_console_log("Creating scheduler...");
	initialize_scheduler();
}

ScrapEngine::Render::RenderManager::~RenderManager()
{
	Debug::DebugLog::print_to_console_log("Deleting ~RenderManager");
	delete_queues();
	cleanup_swap_chain();
	delete render_camera_;

	delete skybox_;
	for (auto current_model : loaded_models_)
	{
		delete current_model;
	}
	VulkanModelBuffersPool::get_instance()->clear_memory();
	VulkanModelPool::get_instance()->clear_memory();
	VulkanSimpleMaterialPool::get_instance()->clear_memory();
	delete vulkan_render_semaphores_;
	delete vulkan_render_command_pool_;
	delete vulkan_render_device_;
	delete vulkan_window_surface_;
	delete vulkan_instance_;
	delete game_window_;
	if (g_TS.GetNumTaskThreads() != 0 || g_TS.GetThreadNum() != 0)
	{
		Debug::DebugLog::print_to_console_log("Threads > 0, shutting down scheduler...");
		g_TS.WaitforAllAndShutdown();
	}
	Debug::DebugLog::print_to_console_log("Deleting ~RenderManager completed");
}

void ScrapEngine::Render::RenderManager::cleanup_swap_chain()
{
	Debug::DebugLog::print_to_console_log("---cleanupSwapChain()---");
	delete vulkan_render_color_;
	delete vulkan_render_depth_;
	delete vulkan_render_frame_buffer_;
	delete_command_buffers();
	for (auto& loaded_model : loaded_models_)
	{
		for (auto model_material : (*loaded_model->get_mesh_materials()))
		{
			model_material->delete_graphics_pipeline();
		}
	}
	delete vulkan_rendering_pass_;
	delete vulkan_render_image_view_;
	delete vulkan_render_swap_chain_;
	Debug::DebugLog::print_to_console_log("---cleanupSwapChain() completed---");
}

void ScrapEngine::Render::RenderManager::delete_queues() const
{
	delete vulkan_graphics_queue_;
	delete vulkan_presentation_queue_;
}

void ScrapEngine::Render::RenderManager::delete_command_buffers() const
{
	for (threaded_command_buffer cb : command_buffers_)
	{
		cb.command_buffer->free_command_buffers();
		delete cb.command_buffer;
		delete cb.command_pool;
	}
}

ScrapEngine::Render::GameWindow* ScrapEngine::Render::RenderManager::get_game_window() const
{
	return game_window_;
}

ScrapEngine::Render::Camera* ScrapEngine::Render::RenderManager::get_render_camera() const
{
	return render_camera_;
}

ScrapEngine::Render::Camera* ScrapEngine::Render::RenderManager::get_default_render_camera() const
{
	return default_camera_;
}

void ScrapEngine::Render::RenderManager::set_render_camera(Camera* new_camera)
{
	render_camera_ = new_camera;
}

void ScrapEngine::Render::RenderManager::initialize_vulkan(const game_base_info* received_base_game_info)
{
	Debug::DebugLog::print_to_console_log("---initializeVulkan()---");
	vulkan_instance_ = VukanInstance::get_instance();
	vulkan_instance_->init(received_base_game_info->app_name, received_base_game_info->app_version,
	                       "ScrapEngine");
	Debug::DebugLog::print_to_console_log("VulkanInstance created");
	vulkan_window_surface_ = VulkanSurface::get_instance();
	vulkan_window_surface_->init(game_window_);
	Debug::DebugLog::print_to_console_log("VulkanWindowSurface created");
	vulkan_render_device_ = VulkanDevice::get_instance();
	vulkan_render_device_->init(vulkan_instance_->get_vulkan_instance(), vulkan_window_surface_->get_surface());
	Debug::DebugLog::print_to_console_log("VulkanRenderDevice created");
	create_queues();
	vulkan_render_swap_chain_ = new VulkanSwapChain(
		vulkan_render_device_->query_swap_chain_support(vulkan_render_device_->get_physical_device()),
		vulkan_render_device_->get_cached_queue_family_indices(),
		vulkan_window_surface_->get_surface(), received_base_game_info->window_width,
		received_base_game_info->window_height, received_base_game_info->vsync);
	Debug::DebugLog::print_to_console_log("VulkanSwapChain created");
	vulkan_render_image_view_ = new VulkanImageView(vulkan_render_swap_chain_);
	Debug::DebugLog::print_to_console_log("VulkanImageView created");
	vulkan_rendering_pass_ = VulkanRenderPass::get_instance();
	vulkan_rendering_pass_->init(vulkan_render_swap_chain_->get_swap_chain_image_format(),
	                             vulkan_render_device_->get_msaa_samples());
	Debug::DebugLog::print_to_console_log("VulkanRenderPass created");
	vulkan_render_command_pool_ = SingletonCommandPool::get_instance();
	vulkan_render_command_pool_->init(vulkan_render_device_->get_cached_queue_family_indices());
	Debug::DebugLog::print_to_console_log("VulkanCommandPool created");
	vulkan_render_color_ = new VulkanColorResources(vulkan_render_device_->get_msaa_samples(),
	                                                vulkan_render_swap_chain_);
	Debug::DebugLog::print_to_console_log("VulkanRenderColor created");
	vulkan_render_depth_ = new VulkanDepthResources(&vulkan_render_swap_chain_->get_swap_chain_extent(),
	                                                vulkan_render_device_->get_msaa_samples());
	Debug::DebugLog::print_to_console_log("VulkanDepthResources created");
	vulkan_render_frame_buffer_ = new VulkanFrameBuffer(vulkan_render_image_view_,
	                                                    &vulkan_render_swap_chain_->get_swap_chain_extent(),
	                                                    vulkan_render_depth_->get_depth_image_view(),
	                                                    vulkan_render_color_->get_color_image_view());
	Debug::DebugLog::print_to_console_log("VulkanFrameBuffer created");
	//Create both empty CommandBuffers
	Debug::DebugLog::print_to_console_log("Creating command buffers...");
	initialize_command_buffers();
	Debug::DebugLog::print_to_console_log("Command buffers created!");
	//Vulkan Semaphores
	vulkan_render_semaphores_ = new VulkanSemaphoresManager();
	image_available_semaphores_ref_ = vulkan_render_semaphores_->get_image_available_semaphores_vector();
	render_finished_semaphores_ref_ = vulkan_render_semaphores_->get_render_finished_semaphores_vector();
	in_flight_fences_ref_ = vulkan_render_semaphores_->get_in_flight_fences_vector();
	Debug::DebugLog::print_to_console_log("VulkanSemaphoresManager created");
	create_camera();
	Debug::DebugLog::print_to_console_log("User View Camera created");
	Debug::DebugLog::print_to_console_log("---initializeVulkan() completed---");
}

void ScrapEngine::Render::RenderManager::initialize_scheduler()
{
	//Initialize enkiTS scheduler
	g_TS.Initialize();
}

void ScrapEngine::Render::RenderManager::initialize_command_buffers()
{
	for (int i = 0; i < 2; i++)
	{
		command_buffers_.push_back(threaded_command_buffer());
		command_buffers_[i].command_pool = new StandardCommandPool();
		command_buffers_[i].command_pool->init(vulkan_render_device_->get_cached_queue_family_indices());
		command_buffers_[i].command_buffer = new VulkanCommandBuffer();
		//Add a task
		command_buffers_tasks_.push_back(new ParallelCommandBufferCreation());
		command_buffers_tasks_[i]->owner = this;
	}
	command_buffers_tasks_[1]->flip_flop = true;
}

void ScrapEngine::Render::RenderManager::prepare_to_draw_frame()
{
	create_command_buffer(false);
}

void ScrapEngine::Render::RenderManager::create_queues()
{
	Debug::DebugLog::print_to_console_log("---Begin queues creation---");
	//_graphics_queue
	GraphicsQueue* g_queue = GraphicsQueue::get_instance();
	g_queue->init(vulkan_render_device_->get_cached_queue_family_indices());
	vulkan_graphics_queue_ = g_queue;
	//presentation_queue
	PresentQueue* p_queue = PresentQueue::get_instance();
	p_queue->init(vulkan_render_device_->get_cached_queue_family_indices());
	vulkan_presentation_queue_ = p_queue;
	Debug::DebugLog::print_to_console_log("---Ended queues creation---");
}

void ScrapEngine::Render::RenderManager::create_command_buffer(const bool flip_flop)
{
	const short int index = flip_flop ? 1 : 0;
	command_buffers_[index].command_buffer->free_command_buffers();
	command_buffers_[index].command_buffer->init_command_buffer(vulkan_render_frame_buffer_,
	                                                            &vulkan_render_swap_chain_->get_swap_chain_extent(),
	                                                            command_buffers_[index].command_pool);
	if (skybox_)
	{
		command_buffers_[index].command_buffer->load_skybox(skybox_);
	}
	for (auto mesh : loaded_models_)
	{
		command_buffers_[index].command_buffer->load_mesh(mesh);
	}
	command_buffers_[index].command_buffer->close_command_buffer();
}

void ScrapEngine::Render::RenderManager::check_start_new_thread()
{
	const short int index = command_buffer_flip_flop_ ? 0 : 1;
	if (!command_buffers_[index].is_running)
	{
		command_buffers_[index].is_running = true;
		g_TS.AddTaskSetToPipe(command_buffers_tasks_[index]);
	}
}

void ScrapEngine::Render::RenderManager::swap_command_buffers()
{
	if (current_frame_ >= 1)
	{
		const short int index = command_buffer_flip_flop_ ? 0 : 1;
		if (command_buffers_[index].is_running && command_buffers_tasks_[index]->GetIsComplete())
		{
			waiting_fence_ = &(*in_flight_fences_ref_)[current_frame_];
			command_buffers_[index].is_running = false;
			command_buffer_flip_flop_ = !command_buffer_flip_flop_;
		}
	}
}

ScrapEngine::Render::VulkanMeshInstance* ScrapEngine::Render::RenderManager::load_mesh(
	const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path,
	const std::vector<std::string>& textures_path)
{
	loaded_models_.push_back(
		new VulkanMeshInstance(vertex_shader_path, fragment_shader_path, model_path, textures_path,
		                       vulkan_render_swap_chain_)
	);
	return loaded_models_.back();
}

ScrapEngine::Render::VulkanMeshInstance* ScrapEngine::Render::RenderManager::load_mesh(
	const std::string& model_path, const std::vector<std::string>& textures_path)
{
	return load_mesh("../assets/shader/compiled_shaders/shader_base.vert.spv",
	                 "../assets/shader/compiled_shaders/shader_base.frag.spv", model_path, textures_path);
}

void ScrapEngine::Render::RenderManager::unload_mesh(VulkanMeshInstance* mesh_to_unload)
{
	const std::vector<VulkanMeshInstance*>::iterator element = find(loaded_models_.begin(), loaded_models_.end(),
	                                                                mesh_to_unload);
	if (element != loaded_models_.end())
	{
		delete *element;
		loaded_models_.erase(element);
	}
}

ScrapEngine::Render::VulkanSkyboxInstance* ScrapEngine::Render::RenderManager::load_skybox(
	const std::array<std::string, 6>& files_path)
{
	delete skybox_;

	skybox_ = new VulkanSkyboxInstance("../assets/shader/compiled_shaders/skybox.vert.spv",
	                                   "../assets/shader/compiled_shaders/skybox.frag.spv",
	                                   "../assets/models/cube.obj",
	                                   files_path, vulkan_render_swap_chain_);
	return skybox_;
}

void ScrapEngine::Render::RenderManager::draw_frame()
{
	//Check if i can build another command buffer in background
	check_start_new_thread();
	VulkanDevice::get_instance()->get_logical_device()->waitForFences(1, &(*in_flight_fences_ref_)[current_frame_],
	                                                                  true,
	                                                                  std::numeric_limits<uint64_t>::max());

	result_ = VulkanDevice::get_instance()->get_logical_device()->acquireNextImageKHR(
		vulkan_render_swap_chain_->get_swap_chain(),
		std::numeric_limits<uint64_t>::max(),
		(*image_available_semaphores_ref_)[current_frame_], vk::Fence(),
		&image_index_);

	if (result_ == vk::Result::eErrorOutOfDateKHR)
	{
		//recreateSwapChain();
		throw std::runtime_error("recreateSwapChain() not ready!");
	}
	else if (result_ != vk::Result::eSuccess && result_ != vk::Result::eSuboptimalKHR)
	{
		throw std::runtime_error("RenderManager: Failed to acquire swap chain image!");
	}
	//Update uniform buffer
	for (auto& loaded_model : loaded_models_)
	{
		loaded_model->update_uniform_buffer(image_index_, render_camera_);
	}
	if (skybox_)
	{
		skybox_->update_uniform_buffer(image_index_, render_camera_);
	}
	//Submit the frame
	vk::SubmitInfo submit_info;

	vk::Semaphore wait_semaphores[] = {(*image_available_semaphores_ref_)[current_frame_]};;

	vk::PipelineStageFlags wait_stages[] = {vk::PipelineStageFlagBits::eColorAttachmentOutput};

	submit_info.setWaitSemaphoreCount(1);
	submit_info.setPWaitSemaphores(wait_semaphores);
	submit_info.setPWaitDstStageMask(wait_stages);

	submit_info.setCommandBufferCount(1);
	submit_info.setPCommandBuffers(
		&(*command_buffers_[command_buffer_flip_flop_].command_buffer->get_command_buffers_vector())[image_index_]);

	vk::Semaphore signal_semaphores[] = {(*render_finished_semaphores_ref_)[current_frame_]};
	submit_info.setSignalSemaphoreCount(1);
	submit_info.setPSignalSemaphores(signal_semaphores);

	VulkanDevice::get_instance()->get_logical_device()->resetFences(1, &(*in_flight_fences_ref_)[current_frame_]);

	result_ = vulkan_graphics_queue_->get_queue()->submit(1, &submit_info,
	                                                      (*in_flight_fences_ref_)[current_frame_]);
	if (result_ != vk::Result::eSuccess)
	{
		std::cout << "RESULT TYPE:" << result_ << std::endl;
		throw std::runtime_error("RenderManager: Failed to submit draw command buffer!");
	}

	vk::PresentInfoKHR present_info;

	present_info.setWaitSemaphoreCount(1);
	present_info.setPWaitSemaphores(signal_semaphores);

	vk::SwapchainKHR swap_chains[] = {vulkan_render_swap_chain_->get_swap_chain()};
	present_info.setSwapchainCount(1);
	present_info.setPSwapchains(swap_chains);

	present_info.setPImageIndices(&image_index_);

	result_ = vulkan_presentation_queue_->get_queue()->presentKHR(&present_info);

	if (result_ == vk::Result::eErrorOutOfDateKHR || result_ == vk::Result::eSuboptimalKHR || framebuffer_resized_)
	{
		//framebufferResized = false;
		//recreateSwapChain();
		throw std::runtime_error("recreateSwapChain() not ready!");
	}
	else if (result_ != vk::Result::eSuccess)
	{
		throw std::runtime_error("RenderManager: Failed to present swap chain image!");
	}

	//Check if i can swap the command buffers
	swap_command_buffers();
	//Update the current frame index
	current_frame_ = (current_frame_ + 1) % max_frames_in_flight_;
}

void ScrapEngine::Render::RenderManager::wait_device_idle() const
{
	vulkan_render_device_->get_logical_device()->waitIdle();
}

void ScrapEngine::Render::RenderManager::recreate_swap_chain()
{
	VulkanDevice::get_instance()->get_logical_device()->waitIdle();
	//TODO https://vulkan-tutorial.com/Drawing_a_triangle/Swap_chain_recreation
}

void ScrapEngine::Render::RenderManager::create_camera()
{
	render_camera_ = new Camera();
	default_camera_ = render_camera_;
}
