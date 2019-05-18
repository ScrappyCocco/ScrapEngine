#include "RenderManager.h"


ScrapEngine::Render::RenderManager::RenderManager(const ScrapEngine::game_base_info* received_base_game_info)
{
	GameWindow = new ScrapEngine::Render::GameWindow(received_base_game_info->window_width, received_base_game_info->window_height, received_base_game_info->app_name);
	Debug::DebugLog::print_to_console_log("GameWindow created");
	initializeVulkan(received_base_game_info);
}

ScrapEngine::Render::RenderManager::~RenderManager()
{
	Debug::DebugLog::print_to_console_log("Deleting ~RenderManager");
	deleteQueues();
	cleanupSwapChain();
	delete RenderCamera;

	delete Skybox;
	for (ScrapEngine::Render::VulkanMeshInstance* current_model : LoadedModels) {
		delete current_model;
	}
	delete VulkanRenderSemaphores;
	delete VulkanRenderCommandPool;
	delete VulkanRenderDevice;
	delete VulkanWindowSurface;
	delete VulkanInstance;
	delete GameWindow;
	Debug::DebugLog::print_to_console_log("Deleting ~RenderManager completed");
}

void ScrapEngine::Render::RenderManager::cleanupSwapChain()
{
	Debug::DebugLog::print_to_console_log("---cleanupSwapChain()---");
	delete VulkanRenderColor;
	delete VulkanRenderDepth;
	delete VulkanRenderFrameBuffer;
	deleteCommandBuffers();
	for (int i = 0; i < LoadedModels.size(); i++) {
		LoadedModels[i]->deleteGraphicsPipeline();
	}
	delete VulkanRenderingPass;
	delete VulkanRenderImageView;
	delete VulkanRenderSwapChain;
	Debug::DebugLog::print_to_console_log("---cleanupSwapChain() completed---");
}

void ScrapEngine::Render::RenderManager::deleteQueues()
{
	delete VulkanGraphicsQueue;
	delete VulkanPresentationQueue;
}

void ScrapEngine::Render::RenderManager::deleteCommandBuffers()
{
	VulkanRenderCommandBuffer->free_command_buffers();
	delete VulkanRenderCommandBuffer;
}

ScrapEngine::Render::GameWindow* ScrapEngine::Render::RenderManager::getGameWindow() const
{
	return GameWindow;
}

ScrapEngine::Render::Camera* ScrapEngine::Render::RenderManager::getRenderCamera() const
{
	return RenderCamera;
}

ScrapEngine::Render::Camera* ScrapEngine::Render::RenderManager::getDefaultRenderCamera() const
{
	return defaultCamera;
}

void ScrapEngine::Render::RenderManager::setRenderCamera(ScrapEngine::Render::Camera* newCamera)
{
	RenderCamera = newCamera;
}

void ScrapEngine::Render::RenderManager::initializeVulkan(const ScrapEngine::game_base_info* received_base_game_info)
{
	Debug::DebugLog::print_to_console_log("---initializeVulkan()---");
	VulkanInstance = new VukanInstance(received_base_game_info->app_name, received_base_game_info->app_version, "ScrapEngine");
	Debug::DebugLog::print_to_console_log("VulkanInstance created");
	VulkanWindowSurface = new VulkanSurface(GameWindow);
	Debug::DebugLog::print_to_console_log("VulkanWindowSurface created");
	VulkanRenderDevice = new VulkanDevice(VulkanInstance->get_vulkan_instance(), VulkanWindowSurface->getSurface());
	Debug::DebugLog::print_to_console_log("VulkanRenderDevice created");
	createQueues();
	VulkanRenderSwapChain = new VulkanSwapChain(VulkanRenderDevice->query_swap_chain_support(VulkanRenderDevice->get_physical_device()),
		VulkanRenderDevice->get_cached_queue_family_indices(),
		VulkanWindowSurface->getSurface(), received_base_game_info->window_width, received_base_game_info->window_height, received_base_game_info->vsync);
	Debug::DebugLog::print_to_console_log("VulkanSwapChain created");
	VulkanRenderImageView = new VulkanImageView(VulkanRenderSwapChain);
	Debug::DebugLog::print_to_console_log("VulkanImageView created");
	VulkanRenderingPass = new VulkanRenderPass(VulkanRenderSwapChain->getSwapChainImageFormat(), VulkanRenderDevice->get_msaa_samples());
	Debug::DebugLog::print_to_console_log("VulkanRenderPass created");
	VulkanRenderCommandPool = new VulkanCommandPool(VulkanRenderDevice->get_cached_queue_family_indices());
	Debug::DebugLog::print_to_console_log("VulkanCommandPool created");
	VulkanRenderColor = new VulkanColorResources(VulkanRenderDevice->get_msaa_samples(), VulkanRenderSwapChain);
	Debug::DebugLog::print_to_console_log("VulkanRenderColor created");
	VulkanRenderDepth = new VulkanDepthResources(&VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderDevice->get_msaa_samples());
	Debug::DebugLog::print_to_console_log("VulkanDepthResources created");
	VulkanRenderFrameBuffer = new VulkanFrameBuffer(VulkanRenderImageView, &VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderDepth->get_depth_image_view(), VulkanRenderColor->getColorImageView());
	Debug::DebugLog::print_to_console_log("VulkanFrameBuffer created");
	//Create empty CommandBuffers
	createCommandBuffers();
	//Vulkan Semaphores
	VulkanRenderSemaphores = new VulkanSemaphoresManager();
	imageAvailableSemaphoresRef = VulkanRenderSemaphores->getImageAvailableSemaphoresVector();
	renderFinishedSemaphoresRef = VulkanRenderSemaphores->getRenderFinishedSemaphoresVector();
	inFlightFencesRef = VulkanRenderSemaphores->getInFlightFencesVector();
	Debug::DebugLog::print_to_console_log("VulkanSemaphoresManager created");
	createCamera();
	Debug::DebugLog::print_to_console_log("User View Camera created");
	Debug::DebugLog::print_to_console_log("---initializeVulkan() completed---");
}

void ScrapEngine::Render::RenderManager::createQueues()
{
	Debug::DebugLog::print_to_console_log("---Begin queues creation---");
	VulkanGraphicsQueue = new GraphicsQueue(VulkanRenderDevice->get_cached_queue_family_indices());
	VulkanPresentationQueue = new PresentQueue(VulkanRenderDevice->get_cached_queue_family_indices());
	Debug::DebugLog::print_to_console_log("---Ended queues creation---");
}

void ScrapEngine::Render::RenderManager::createCommandBuffers()
{
	std::vector<ScrapEngine::Render::VulkanGraphicsPipeline*> pipelines;
	std::vector<const std::vector<vk::DescriptorSet>*> descriptorSets;
	std::vector<ScrapEngine::simple_buffer<Vertex>*> vertexbuffers;
	std::vector<ScrapEngine::simple_buffer<uint32_t>*> indexbuffers;
	for (ScrapEngine::Render::VulkanMeshInstance* mesh : LoadedModels) {
		pipelines.push_back(mesh->getVulkanRenderGraphicsPipeline());
		descriptorSets.push_back(mesh->getVulkanRenderDescriptorSet()->get_descriptor_sets());
		vertexbuffers.push_back(mesh->getVertexbuffer());
		indexbuffers.push_back(mesh->getIndexbuffer());
	}
	VulkanRenderCommandBuffer = new VulkanCommandBuffer(
		VulkanRenderFrameBuffer,
		&VulkanRenderSwapChain->getSwapChainExtent(),
		pipelines,
		descriptorSets,
		vertexbuffers,
		indexbuffers,
		Skybox
	);
	Debug::DebugLog::print_to_console_log("VulkanRenderCommandBuffer created");
}

ScrapEngine::Render::VulkanMeshInstance* ScrapEngine::Render::RenderManager::loadMesh(const std::string & vertex_shader_path, const std::string & fragment_shader_path, const std::string & model_path, const std::string & texture_path)
{
	LoadedModels.push_back(
		new VulkanMeshInstance(vertex_shader_path, fragment_shader_path, model_path, texture_path,VulkanRenderDevice, VulkanRenderSwapChain)
	);
	deleteCommandBuffers();
	createCommandBuffers();
	return LoadedModels.back();
}

ScrapEngine::Render::VulkanMeshInstance* ScrapEngine::Render::RenderManager::loadMesh(const std::string & model_path, const std::string & texture_path)
{
	return loadMesh("../assets/shader/compiled_shaders/shader_base.vert.spv", "../assets/shader/compiled_shaders/shader_base.frag.spv", model_path, texture_path);
}

void ScrapEngine::Render::RenderManager::unloadMesh(ScrapEngine::Render::VulkanMeshInstance* meshToUnload)
{
	std::vector<ScrapEngine::Render::VulkanMeshInstance*>::iterator element = find(LoadedModels.begin(), LoadedModels.end(), meshToUnload);
	if (element != LoadedModels.end())
	{
		delete *element;
		LoadedModels.erase(element);
		deleteCommandBuffers();
		createCommandBuffers();
	}
}

ScrapEngine::Render::VulkanSkyboxInstance* ScrapEngine::Render::RenderManager::loadSkybox(const std::array<std::string, 6>& files_path)
{
	if (Skybox) {
		delete Skybox;
	}
	Skybox = new VulkanSkyboxInstance("../assets/shader/compiled_shaders/skybox.vert.spv", "../assets/shader/compiled_shaders/skybox.frag.spv", "../assets/models/cube.obj", files_path, VulkanRenderDevice, VulkanRenderSwapChain);
	deleteCommandBuffers();
	createCommandBuffers();
	return Skybox;
}

void ScrapEngine::Render::RenderManager::drawFrame()
{
	VulkanDevice::static_logic_device_ref->waitForFences(1, &(*inFlightFencesRef)[currentFrame], true, std::numeric_limits<uint64_t>::max());

	result = VulkanDevice::static_logic_device_ref->acquireNextImageKHR(VulkanRenderSwapChain->getSwapChain(), std::numeric_limits<uint64_t>::max(), (*imageAvailableSemaphoresRef)[currentFrame], vk::Fence(), &imageIndex);

	if (result == vk::Result::eErrorOutOfDateKHR) {
		//recreateSwapChain();
		throw std::runtime_error("recreateSwapChain() not ready!");
		return;
	}
	else if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR) {
		throw std::runtime_error("RenderManager: Failed to acquire swap chain image!");
	}
	//Update uniform buffer
	for (int i = 0;i < LoadedModels.size(); i++) {
		LoadedModels[i]->updateUniformBuffer(imageIndex, RenderCamera);
	}
	if (Skybox) {
		Skybox->updateUniformBuffer(imageIndex, RenderCamera);
	}
	//Submit the frame
	vk::SubmitInfo submitInfo;

	vk::Semaphore waitSemaphores[] = { (*imageAvailableSemaphoresRef)[currentFrame] };;

	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };

	submitInfo.setWaitSemaphoreCount(1);
	submitInfo.setPWaitSemaphores(waitSemaphores);
	submitInfo.setPWaitDstStageMask(waitStages);

	submitInfo.setCommandBufferCount(1);
	submitInfo.setPCommandBuffers(&(*VulkanRenderCommandBuffer->get_command_buffers_vector())[imageIndex]);

	vk::Semaphore signalSemaphores[] = { (*renderFinishedSemaphoresRef)[currentFrame] };
	submitInfo.setSignalSemaphoreCount(1);
	submitInfo.setPSignalSemaphores(signalSemaphores);
	
	VulkanDevice::static_logic_device_ref->resetFences(1, &(*inFlightFencesRef)[currentFrame]);

	result = VulkanGraphicsQueue->getgraphicsQueue()->submit(1, &submitInfo, (*inFlightFencesRef)[currentFrame]);
	if (result != vk::Result::eSuccess) {
		std::cout << "RESULT TYPE:" << result << std::endl;
		throw std::runtime_error("RenderManager: Failed to submit draw command buffer!");
	}

	vk::PresentInfoKHR presentInfo;

	presentInfo.setWaitSemaphoreCount(1);
	presentInfo.setPWaitSemaphores(signalSemaphores);
	
	vk::SwapchainKHR swapChains[] = { VulkanRenderSwapChain->getSwapChain() };
	presentInfo.setSwapchainCount(1);
	presentInfo.setPSwapchains(swapChains);

	presentInfo.setPImageIndices(&imageIndex);

	result = VulkanPresentationQueue->getPresentQueue()->presentKHR(&presentInfo);

	if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR || framebufferResized) {
		//framebufferResized = false;
		//recreateSwapChain();
		throw std::runtime_error("recreateSwapChain() not ready!");
	}
	else if (result != vk::Result::eSuccess) {
		throw std::runtime_error("RenderManager: Failed to present swap chain image!");
	}
		
	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void ScrapEngine::Render::RenderManager::waitDeviceIdle()
{
	VulkanRenderDevice->get_logical_device()->waitIdle();
}

void ScrapEngine::Render::RenderManager::recreateSwapChain()
{
	VulkanDevice::static_logic_device_ref->waitIdle();
	//TODO https://vulkan-tutorial.com/Drawing_a_triangle/Swap_chain_recreation
}

void ScrapEngine::Render::RenderManager::createCamera()
{
	RenderCamera = new Camera();
	defaultCamera = RenderCamera;
}
