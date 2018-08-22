#include "EngineManager.h"

#include <thread>
#include "../Rendering/Base/SimpleTestData.h"

ScrapEngine::EngineManager::EngineManager(std::string app_name, int app_version, uint32_t window_WIDTH, uint32_t window_HEIGHT, bool fullscreen)
	: received_base_game_info(app_name, app_version, window_WIDTH, window_HEIGHT, fullscreen)
{
	initializeEngine();
}

ScrapEngine::EngineManager::~EngineManager()
{
	if (!cleanupDone) { //Check if the cleanup has already been done
		cleanupEngine();
	}
}

void ScrapEngine::EngineManager::StartGameLoop()
{
	//Execute game loop until end
	mainGameLoop();
	//Execution ended, close the engine
	cleanupEngine();
	DebugLog::printToConsoleLog("---Engine Execution ended---");
}

void ScrapEngine::EngineManager::initializeEngine()
{
	DebugLog::printToConsoleLog("---initializeEngine()---");

	GameWindow = new ScrapEngine::GameWindow(received_base_game_info.window_WIDTH, received_base_game_info.window_HEIGHT, received_base_game_info.app_name);
	DebugLog::printToConsoleLog("GameWindow created");
	initializeVulkan();
	DebugLog::printToConsoleLog("---initializeEngine() completed---");

	DebugLog::printToConsoleLog("---Engine Execution ended---");
}

void ScrapEngine::EngineManager::initializeVulkan()
{
	DebugLog::printToConsoleLog("---initializeVulkan()---");

	VulkanInstance = new VukanInstance(received_base_game_info.app_name, received_base_game_info.app_version, "ScrapEngine");
	DebugLog::printToConsoleLog("VulkanInstance created");
	VulkanWindowSurface = new VulkanSurface(VulkanInstance, GameWindow);
	DebugLog::printToConsoleLog("VulkanWindowSurface created");
	VulkanRenderDevice = new VulkanDevice(VulkanInstance->getVulkanInstance(), VulkanWindowSurface->getSurface());
	deviceRef = VulkanRenderDevice->getLogicalDevice();
	DebugLog::printToConsoleLog("VulkanRenderDevice created");
	createQueues();
	VulkanRenderSwapChain = new VulkanSwapChain(VulkanRenderDevice->querySwapChainSupport(VulkanRenderDevice->getPhysicalDevice()),
		VulkanRenderDevice->getCachedQueueFamilyIndices(),
		deviceRef, VulkanWindowSurface->getSurface(), received_base_game_info.window_WIDTH, received_base_game_info.window_HEIGHT);
	DebugLog::printToConsoleLog("VulkanSwapChain created");
	VulkanRenderImageView = new VulkanImageView(deviceRef, VulkanRenderSwapChain);
	DebugLog::printToConsoleLog("VulkanImageView created");
	VulkanRenderingPass = new VulkanRenderPass(deviceRef, VulkanRenderSwapChain->getSwapChainImageFormat(), VulkanRenderDevice->getPhysicalDevice(), VulkanRenderDevice->getMsaaSamples());
	DebugLog::printToConsoleLog("VulkanRenderPass created");
	VulkanRenderDescriptorSet = new VulkanDescriptorSet(deviceRef);
	DebugLog::printToConsoleLog("VulkanDescriptorSet created");
	VulkanRenderGraphicsPipeline = new VulkanGraphicsPipeline("../assets/shader/vert.spv", "../assets/shader/frag.spv", deviceRef, VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderingPass->getRenderPass(), VulkanRenderDescriptorSet->getDescriptorSetLayout(), VulkanRenderDevice->getMsaaSamples());
	DebugLog::printToConsoleLog("VulkanGraphicsPipeline created");
	VulkanRenderCommandPool = new VulkanCommandPool(VulkanRenderDevice->getCachedQueueFamilyIndices(), deviceRef);
	DebugLog::printToConsoleLog("VulkanCommandPool created");
	VulkanRenderColor = new VulkanColorResources(deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue(), VulkanRenderDevice->getMsaaSamples(), VulkanRenderSwapChain);
	DebugLog::printToConsoleLog("VulkanRenderColor created");
	VulkanRenderDepth = new VulkanDepthResources(deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue(), &VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderDevice->getMsaaSamples());
	DebugLog::printToConsoleLog("VulkanDepthResources created");
	VulkanRenderFrameBuffer = new VulkanFrameBuffer(VulkanRenderImageView, VulkanRenderingPass->getRenderPass(), deviceRef, &VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderDepth->getDepthImageView(), VulkanRenderingPass->getRenderPass(), VulkanRenderColor->getColorImageView());
	DebugLog::printToConsoleLog("VulkanFrameBuffer created");
	//Yes, I'd say that you'd have something like a pipeline per material type, and vertex buffers + uniform buffers + command buffers per model.
	//VulkanTextureImage = new TextureImage("../assets/texture/statue.jpg", deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	VulkanTextureImage = new TextureImage("../assets/textures/chalet.jpg", deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	//VulkanTextureImage = new TextureImage("../assets/textures/SimpleTexture.png", deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	DebugLog::printToConsoleLog("TextureImage created");
	VulkanTextureImageView = new TextureImageView(deviceRef, VulkanTextureImage->getTextureImage(), VulkanTextureImage->getMipLevels());
	DebugLog::printToConsoleLog("TextureImageView created");
	VulkanTextureSampler = new TextureSampler(deviceRef, VulkanTextureImage->getMipLevels());
	DebugLog::printToConsoleLog("TextureSampler created");
	//VulkanRenderModel = new VulkanModel("../assets/models/SimpleCube.obj", "../assets/textures/SimpleTexture.png");
	VulkanRenderModel = new VulkanModel("../assets/models/chalet.obj", "../assets/textures/SimpleTexture.png");
	DebugLog::printToConsoleLog("VulkanModel loaded");
	//POSSIBLE TO MOVE getPhysicalDevice IN MEMORY MANAGER AND CREATE A CLASS FOR IT?
	//VulkanRenderVertexBuffer = new VertexBuffer(deviceRef, VulkanRenderDevice->getPhysicalDevice(), &vertices, VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	VulkanRenderVertexBuffer = new VertexBuffer(deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderModel->getVertices(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	DebugLog::printToConsoleLog("VertexBuffer created");
	//VulkanRenderIndexBuffer = new IndexBuffer(deviceRef, VulkanRenderDevice->getPhysicalDevice(), &indices, VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	VulkanRenderIndexBuffer = new IndexBuffer(deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderModel->getIndices(), VulkanRenderCommandPool->getCommandPool(), VulkanGraphicsQueue->getgraphicsQueue());
	DebugLog::printToConsoleLog("IndexBuffer created");
	VulkanRenderUniformBuffer = new UniformBuffer(deviceRef, VulkanRenderDevice->getPhysicalDevice(), VulkanRenderSwapChain->getSwapChainImagesVector());
	DebugLog::printToConsoleLog("UniformBuffer created");
	VulkanRenderDescriptorPool = new VulkanDescriptorPool(deviceRef, VulkanRenderSwapChain->getSwapChainImagesVector());
	DebugLog::printToConsoleLog("VulkanDescriptorPool created");
	VulkanRenderDescriptorSet->createDescriptorSets(VulkanRenderDescriptorPool->getDescriptorPool(), VulkanRenderSwapChain->getSwapChainImagesVector(), VulkanRenderUniformBuffer->getUniformBuffers(),
		VulkanTextureImageView->getTextureImageView(), VulkanTextureSampler->getTextureSampler());
	DebugLog::printToConsoleLog("(DescriptorSets created)");
	simple_buffer<Vertex> vertexbuffer(VulkanRenderVertexBuffer->getVertexBuffer(), VulkanRenderModel->getVertices());
	simple_buffer<uint32_t> indexbuffer(VulkanRenderIndexBuffer->getIndexBuffer(), VulkanRenderModel->getIndices());
	VulkanRenderCommandBuffer = new VulkanCommandBuffer(VulkanRenderFrameBuffer, deviceRef, VulkanRenderCommandPool->getCommandPool(), VulkanRenderingPass->getRenderPass(),
		VulkanRenderSwapChain->getSwapChainExtent(), VulkanRenderGraphicsPipeline,VulkanRenderDescriptorSet->getDescriptorSets(), vertexbuffer, indexbuffer);
	DebugLog::printToConsoleLog("VulkanCommandBuffer created");
	VulkanRenderSemaphores = new VulkanSemaphoresManager(deviceRef);
	imageAvailableSemaphoresRef = VulkanRenderSemaphores->getImageAvailableSemaphoresVector();
	renderFinishedSemaphoresRef = VulkanRenderSemaphores->getRenderFinishedSemaphoresVector();
	inFlightFencesRef = VulkanRenderSemaphores->getInFlightFencesVector();
	DebugLog::printToConsoleLog("VulkanSemaphoresManager created");
	DebugLog::printToConsoleLog("---initializeVulkan() completed---");
}

void ScrapEngine::EngineManager::createQueues()
{
	DebugLog::printToConsoleLog("---Begin queues creation---");
	VulkanGraphicsQueue = new GraphicsQueue(deviceRef, VulkanRenderDevice->getCachedQueueFamilyIndices());
	VulkanPresentationQueue = new PresentQueue(deviceRef, VulkanRenderDevice->getCachedQueueFamilyIndices());
	DebugLog::printToConsoleLog("---Ended queues creation---");
}

void ScrapEngine::EngineManager::deleteQueues()
{
	delete VulkanGraphicsQueue;
	delete VulkanPresentationQueue;
}

void ScrapEngine::EngineManager::mainGameLoop()
{
	DebugLog::printToConsoleLog("---mainGameLoop() started---");
	while (!GameWindow->checkWindowShouldClose()) {
		drawFrame();
	}
	vkDeviceWaitIdle(VulkanRenderDevice->getLogicalDevice());
	DebugLog::printToConsoleLog("---mainGameLoop() ended---");
}

void ScrapEngine::EngineManager::cleanupSwapChain()
{
	DebugLog::printToConsoleLog("---cleanupSwapChain()---");
	delete VulkanRenderColor;
	delete VulkanRenderDepth;
	delete VulkanRenderFrameBuffer;
	vkFreeCommandBuffers(deviceRef, VulkanRenderCommandPool->getCommandPool(), static_cast<uint32_t>(VulkanRenderCommandBuffer->getCommandBuffersVector()->size()), VulkanRenderCommandBuffer->getCommandBuffersVector()->data());
	delete VulkanRenderCommandBuffer;
	delete VulkanRenderGraphicsPipeline;
	delete VulkanRenderingPass;
	delete VulkanRenderImageView;
	delete VulkanRenderSwapChain;
	DebugLog::printToConsoleLog("---cleanupSwapChain() completed---");
}

void ScrapEngine::EngineManager::cleanupEngine()
{
	DebugLog::printToConsoleLog("---cleanupEngine()---");
	
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
	
	cleanupDone = true;
	DebugLog::printToConsoleLog("---cleanupEngine() completed---");
}

void ScrapEngine::EngineManager::drawFrame() {
	vkWaitForFences(deviceRef, 1, &(*inFlightFencesRef)[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(deviceRef, VulkanRenderSwapChain->getSwapChain(), std::numeric_limits<uint64_t>::max(), (*imageAvailableSemaphoresRef)[currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		//recreateSwapChain();
		throw std::runtime_error("recreateSwapChain() not ready!");
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}

 	VulkanRenderUniformBuffer->updateUniformBuffer(imageIndex, &VulkanRenderSwapChain->getSwapChainExtent());

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { (*imageAvailableSemaphoresRef)[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &((*VulkanRenderCommandBuffer->getCommandBuffersVector())[imageIndex]);

	VkSemaphore signalSemaphores[] = { (*renderFinishedSemaphoresRef)[currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(deviceRef, 1, &(*inFlightFencesRef)[currentFrame]);

	if (vkQueueSubmit(VulkanGraphicsQueue->getgraphicsQueue(), 1, &submitInfo, (*inFlightFencesRef)[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { VulkanRenderSwapChain->getSwapChain() };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(VulkanPresentationQueue->getPresentQueue(), &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		//framebufferResized = false;
		//recreateSwapChain();
		throw std::runtime_error("recreateSwapChain() not ready!");
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void ScrapEngine::EngineManager::recreateSwapChain()
{
	vkDeviceWaitIdle(deviceRef);
	//TODO https://vulkan-tutorial.com/Drawing_a_triangle/Swap_chain_recreation
}

ScrapEngine::GameWindow * ScrapEngine::EngineManager::getGameWindow() const
{
	return GameWindow;
}
