#include "RenderManager.h"

ScrapEngine::RenderManager::RenderManager(const ScrapEngine::game_base_info* received_base_game_info)
{
	GameWindow = new ScrapEngine::GameWindow(received_base_game_info->window_WIDTH, received_base_game_info->window_HEIGHT, received_base_game_info->app_name);
	DebugLog::printToConsoleLog("GameWindow created");
	initializeVulkan(received_base_game_info);
}

ScrapEngine::RenderManager::~RenderManager()
{
	DebugLog::printToConsoleLog("Deleting ~RenderManager");
	deleteQueues();
	cleanupSwapChain();

	delete VulkanTextureSampler;
	delete VulkanTextureImageView;
	delete VulkanTextureImage;
	delete VulkanRenderDescriptorPool;
	delete VulkanRenderDescriptorSet;
	delete VulkanRenderUniformBuffer;
	delete VulkanRenderVertexBuffer;
	delete VulkanRenderSemaphores;
	delete VulkanRenderCommandPool;
	delete VulkanRenderDevice;
	delete VulkanWindowSurface;
	delete VulkanInstance;
	delete GameWindow;
	DebugLog::printToConsoleLog("Deleting ~RenderManager completed");
}

const ScrapEngine::GameWindow * ScrapEngine::RenderManager::getGameWindow() const
{
	return GameWindow;
}

void ScrapEngine::RenderManager::initializeVulkan(const ScrapEngine::game_base_info* received_base_game_info)
{
	DebugLog::printToConsoleLog("---initializeVulkan()---");

	VulkanInstance = new VukanInstance(received_base_game_info->app_name, received_base_game_info->app_version, "ScrapEngine");
	DebugLog::printToConsoleLog("VulkanInstance created");
	VulkanWindowSurface = new VulkanSurface(VulkanInstance, GameWindow);
	DebugLog::printToConsoleLog("VulkanWindowSurface created");
	VulkanRenderDevice = new VulkanDevice(VulkanInstance->getVulkanInstance(), VulkanWindowSurface->getSurface());
	deviceRef = *VulkanRenderDevice->getLogicalDevice();
	DebugLog::printToConsoleLog("VulkanRenderDevice created");
	createQueues();
	VulkanRenderSwapChain = new VulkanSwapChain(VulkanRenderDevice->querySwapChainSupport(VulkanRenderDevice->getPhysicalDevice()),
		VulkanRenderDevice->getCachedQueueFamilyIndices(),
		&deviceRef, VulkanWindowSurface->getSurface(), received_base_game_info->window_WIDTH, received_base_game_info->window_HEIGHT);
	DebugLog::printToConsoleLog("VulkanSwapChain created");
	VulkanRenderImageView = new VulkanImageView(&deviceRef, VulkanRenderSwapChain);
	DebugLog::printToConsoleLog("VulkanImageView created");
	VulkanRenderingPass = new VulkanRenderPass(&deviceRef, VulkanRenderSwapChain->getSwapChainImageFormat(), VulkanRenderDevice->getPhysicalDevice(), VulkanRenderDevice->getMsaaSamples());
	DebugLog::printToConsoleLog("VulkanRenderPass created");
	VulkanRenderDescriptorSet = new VulkanDescriptorSet(&deviceRef);
	DebugLog::printToConsoleLog("VulkanDescriptorSet created");
	VulkanRenderGraphicsPipeline = new VulkanGraphicsPipeline("../assets/shader/vert.spv", "../assets/shader/frag.spv", &deviceRef, &VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderingPass->getRenderPass(), VulkanRenderDescriptorSet->getDescriptorSetLayout(), VulkanRenderDevice->getMsaaSamples());
	DebugLog::printToConsoleLog("VulkanGraphicsPipeline created");
	VulkanRenderCommandPool = new VulkanCommandPool(VulkanRenderDevice->getCachedQueueFamilyIndices(), &deviceRef);
	DebugLog::printToConsoleLog("VulkanCommandPool created");
	VulkanRenderColor = new VulkanColorResources(&deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue(), VulkanRenderDevice->getMsaaSamples(), VulkanRenderSwapChain);
	DebugLog::printToConsoleLog("VulkanRenderColor created");
	VulkanRenderDepth = new VulkanDepthResources(&deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue(), &VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderDevice->getMsaaSamples());
	DebugLog::printToConsoleLog("VulkanDepthResources created");
	VulkanRenderFrameBuffer = new VulkanFrameBuffer(VulkanRenderImageView, &deviceRef, &VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderDepth->getDepthImageView(), VulkanRenderingPass->getRenderPass(), VulkanRenderColor->getColorImageView());
	DebugLog::printToConsoleLog("VulkanFrameBuffer created");
	//Yes, I'd say that you'd have something like a pipeline per material type, and vertex buffers + uniform buffers + command buffers per model.
	VulkanTextureImage = new TextureImage("../assets/textures/SimpleGreenTexture.png", &deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	DebugLog::printToConsoleLog("TextureImage created");
	VulkanTextureImageView = new TextureImageView(&deviceRef, VulkanTextureImage->getTextureImage(), VulkanTextureImage->getMipLevels());
	DebugLog::printToConsoleLog("TextureImageView created");
	VulkanTextureSampler = new TextureSampler(&deviceRef, VulkanTextureImage->getMipLevels());
	DebugLog::printToConsoleLog("TextureSampler created");
	VulkanRenderModel = new VulkanModel("../assets/models/chess/ChessPieces/Queen.fbx");
	DebugLog::printToConsoleLog("VulkanModel loaded");
	//POSSIBLE TO MOVE getPhysicalDevice IN MEMORY MANAGER AND CREATE A CLASS FOR IT?
	VulkanRenderVertexBuffer = new VertexBuffer(&deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderModel->getVertices(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	DebugLog::printToConsoleLog("VertexBuffer created");
	VulkanRenderIndexBuffer = new IndexBuffer(&deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderModel->getIndices(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	DebugLog::printToConsoleLog("IndexBuffer created");
	VulkanRenderUniformBuffer = new UniformBuffer(&deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderSwapChain->getSwapChainImagesVector());
	DebugLog::printToConsoleLog("UniformBuffer created");
	VulkanRenderDescriptorPool = new VulkanDescriptorPool(&deviceRef, VulkanRenderSwapChain->getSwapChainImagesVector());
	DebugLog::printToConsoleLog("VulkanDescriptorPool created");
	VulkanRenderDescriptorSet->createDescriptorSets(VulkanRenderDescriptorPool->getDescriptorPool(), VulkanRenderSwapChain->getSwapChainImagesVector(), VulkanRenderUniformBuffer->getUniformBuffers(),
		VulkanTextureImageView->getTextureImageView(), VulkanTextureSampler->getTextureSampler());
	DebugLog::printToConsoleLog("(DescriptorSets created)");
	simple_buffer<Vertex> vertexbuffer(VulkanRenderVertexBuffer->getVertexBuffer(), VulkanRenderModel->getVertices());
	simple_buffer<uint32_t> indexbuffer(VulkanRenderIndexBuffer->getIndexBuffer(), VulkanRenderModel->getIndices());
	VulkanRenderCommandBuffer = new VulkanCommandBuffer(VulkanRenderFrameBuffer, &deviceRef, VulkanRenderCommandPool->getCommandPool(), VulkanRenderingPass->getRenderPass(),
		&VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderGraphicsPipeline, VulkanRenderDescriptorSet->getDescriptorSets(), vertexbuffer, indexbuffer);
	DebugLog::printToConsoleLog("VulkanCommandBuffer created");
	VulkanRenderSemaphores = new VulkanSemaphoresManager(&deviceRef);
	imageAvailableSemaphoresRef = VulkanRenderSemaphores->getImageAvailableSemaphoresVector();
	renderFinishedSemaphoresRef = VulkanRenderSemaphores->getRenderFinishedSemaphoresVector();
	inFlightFencesRef = VulkanRenderSemaphores->getInFlightFencesVector();
	DebugLog::printToConsoleLog("VulkanSemaphoresManager created");
	DebugLog::printToConsoleLog("---initializeVulkan() completed---");
}

void ScrapEngine::RenderManager::createQueues()
{
	DebugLog::printToConsoleLog("---Begin queues creation---");
	VulkanGraphicsQueue = new GraphicsQueue(&deviceRef, VulkanRenderDevice->getCachedQueueFamilyIndices());
	VulkanPresentationQueue = new PresentQueue(&deviceRef, VulkanRenderDevice->getCachedQueueFamilyIndices());
	DebugLog::printToConsoleLog("---Ended queues creation---");
}

void ScrapEngine::RenderManager::deleteQueues()
{
	delete VulkanGraphicsQueue;
	delete VulkanPresentationQueue;
}

void ScrapEngine::RenderManager::cleanupSwapChain()
{
	DebugLog::printToConsoleLog("---cleanupSwapChain()---");
	delete VulkanRenderColor;
	delete VulkanRenderDepth;
	delete VulkanRenderFrameBuffer;
	deviceRef.freeCommandBuffers(*VulkanRenderCommandPool->getCommandPool(), static_cast<uint32_t>(VulkanRenderCommandBuffer->getCommandBuffersVector()->size()), VulkanRenderCommandBuffer->getCommandBuffersVector()->data());
	delete VulkanRenderCommandBuffer;
	delete VulkanRenderGraphicsPipeline;
	delete VulkanRenderingPass;
	delete VulkanRenderImageView;
	delete VulkanRenderSwapChain;
	DebugLog::printToConsoleLog("---cleanupSwapChain() completed---");
}

void ScrapEngine::RenderManager::drawFrame()
{
	deviceRef.waitForFences(1, &(*inFlightFencesRef)[currentFrame], true, std::numeric_limits<uint64_t>::max());

	uint32_t imageIndex;
	vk::Result result = deviceRef.acquireNextImageKHR(VulkanRenderSwapChain->getSwapChain(), std::numeric_limits<uint64_t>::max(), (*imageAvailableSemaphoresRef)[currentFrame], vk::Fence(), &imageIndex);

	if (result == vk::Result::eErrorOutOfDateKHR) {
		//recreateSwapChain();
		throw std::runtime_error("recreateSwapChain() not ready!");
		return;
	}
	else if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}

	VulkanRenderUniformBuffer->updateUniformBuffer(imageIndex, &VulkanRenderSwapChain->getSwapChainExtent());

	vk::SubmitInfo submitInfo;

	vk::Semaphore waitSemaphores[] = { (*imageAvailableSemaphoresRef)[currentFrame] };;

	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };

	submitInfo.setWaitSemaphoreCount(1);
	submitInfo.setPWaitSemaphores(waitSemaphores);
	submitInfo.setPWaitDstStageMask(waitStages);

	submitInfo.setCommandBufferCount(1);
	submitInfo.setPCommandBuffers(&((*VulkanRenderCommandBuffer->getCommandBuffersVector())[imageIndex]));

	vk::Semaphore signalSemaphores[] = { (*renderFinishedSemaphoresRef)[currentFrame] };
	submitInfo.setSignalSemaphoreCount(1);
	submitInfo.setPSignalSemaphores(signalSemaphores);

	deviceRef.resetFences(1, &(*inFlightFencesRef)[currentFrame]);

	if (VulkanGraphicsQueue->getgraphicsQueue()->submit(1, &submitInfo, (*inFlightFencesRef)[currentFrame]) != vk::Result::eSuccess) {
		throw std::runtime_error("failed to submit draw command buffer!");
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
		throw std::runtime_error("failed to present swap chain image!");
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void ScrapEngine::RenderManager::waitDeviceIdle()
{
	VulkanRenderDevice->getLogicalDevice()->waitIdle();
}

void ScrapEngine::RenderManager::recreateSwapChain()
{
	deviceRef.waitIdle();
	//TODO https://vulkan-tutorial.com/Drawing_a_triangle/Swap_chain_recreation
}
