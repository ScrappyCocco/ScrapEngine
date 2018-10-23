#include "VulkanSkyboxInstance.h"

ScrapEngine::VulkanSkyboxInstance::VulkanSkyboxInstance(const std::string & vertex_shader_path, const std::string & fragment_shader_path, const std::string & model_path, const std::string & texture_path, ScrapEngine::VulkanDevice * RenderDevice, vk::CommandPool * CommandPool, vk::Queue * graphicsQueue, ScrapEngine::VulkanSwapChain * SwapChain, ScrapEngine::VulkanRenderPass * RenderingPass)
{
	vk::Device* device_ref = RenderDevice->getLogicalDevice();
	vk::PhysicalDevice* physical_device_ref = RenderDevice->getPhysicalDevice();
	VulkanRenderDescriptorSet = new VulkanDescriptorSet(device_ref);
	DebugLog::printToConsoleLog("VulkanDescriptorSet created");
	VulkanRenderGraphicsPipeline = new VulkanGraphicsPipeline(vertex_shader_path.c_str(), fragment_shader_path.c_str(), device_ref, &SwapChain->getSwapChainExtent(), RenderingPass->getRenderPass(), VulkanRenderDescriptorSet->getDescriptorSetLayout(), RenderDevice->getMsaaSamples());
	DebugLog::printToConsoleLog("VulkanGraphicsPipeline created");
	SkyboxTexture = new ScrapEngine::SkyboxTexture(std::vector<std::string>{
			"../assets/skybox/back.png",
			"../assets/skybox/bottom.png",
			"../assets/skybox/front.png",
			"../assets/skybox/left.png",
			"../assets/skybox/right.png",
			"../assets/skybox/top.png"
	}, 
		device_ref, physical_device_ref, CommandPool, graphicsQueue);
	DebugLog::printToConsoleLog("TextureImage created");
	VulkanTextureImageView = new TextureImageView(device_ref, SkyboxTexture->getTextureImage(), SkyboxTexture->getMipLevels(), true, 6);
	DebugLog::printToConsoleLog("TextureImageView created");
	VulkanTextureSampler = new TextureSampler(device_ref, SkyboxTexture->getMipLevels());
	VulkanRenderModel = new VulkanModel(model_path);
	DebugLog::printToConsoleLog("VulkanModel loaded");
	VulkanRenderVertexBuffer = new VertexBuffer(device_ref, physical_device_ref, VulkanRenderModel->getVertices(), CommandPool, graphicsQueue);
	DebugLog::printToConsoleLog("VertexBuffer created");
	VulkanRenderIndexBuffer = new IndexBuffer(device_ref, physical_device_ref, VulkanRenderModel->getIndices(), CommandPool, graphicsQueue);
	DebugLog::printToConsoleLog("IndexBuffer created");
	//---
	VulkanRenderUniformBuffer = new SkyboxUniformBuffer(device_ref, physical_device_ref, SwapChain->getSwapChainImagesVector(), SwapChain->getSwapChainExtent());
	//VulkanRenderUniformBuffer = new UniformBuffer(device_ref, physical_device_ref, SwapChain->getSwapChainImagesVector(), SwapChain->getSwapChainExtent());
	//---
	DebugLog::printToConsoleLog("UniformBuffer created");
	VulkanRenderDescriptorPool = new VulkanDescriptorPool(device_ref, SwapChain->getSwapChainImagesVector());
	DebugLog::printToConsoleLog("VulkanDescriptorPool created");
	VulkanRenderDescriptorSet->createDescriptorSets(VulkanRenderDescriptorPool->getDescriptorPool(), SwapChain->getSwapChainImagesVector(), VulkanRenderUniformBuffer->getUniformBuffers(),
		VulkanTextureImageView->getTextureImageView(), VulkanTextureSampler->getTextureSampler(), sizeof(SkyboxUniformBufferObject));
	DebugLog::printToConsoleLog("(DescriptorSets created)");
	vertexbuffer = new simple_buffer<Vertex>(VulkanRenderVertexBuffer->getVertexBuffer(), VulkanRenderModel->getVertices());
	indexbuffer = new simple_buffer<uint32_t>(VulkanRenderIndexBuffer->getIndexBuffer(), VulkanRenderModel->getIndices());
}

ScrapEngine::VulkanSkyboxInstance::~VulkanSkyboxInstance()
{
}

void ScrapEngine::VulkanSkyboxInstance::updateUniformBuffer(uint32_t currentImage, ScrapEngine::Camera* RenderCamera)
{
	VulkanRenderUniformBuffer->updateUniformBuffer(currentImage, ScrapEngine::Transform(), RenderCamera);
}

void ScrapEngine::VulkanSkyboxInstance::deleteGraphicsPipeline()
{
	delete VulkanRenderGraphicsPipeline;
}

ScrapEngine::SkyboxUniformBuffer* ScrapEngine::VulkanSkyboxInstance::getVulkanRenderUniformBuffer()
{
	return VulkanRenderUniformBuffer;
}

ScrapEngine::VulkanGraphicsPipeline * ScrapEngine::VulkanSkyboxInstance::getVulkanRenderGraphicsPipeline()
{
	return VulkanRenderGraphicsPipeline;
}

ScrapEngine::VulkanDescriptorSet * ScrapEngine::VulkanSkyboxInstance::getVulkanRenderDescriptorSet()
{
	return VulkanRenderDescriptorSet;
}

ScrapEngine::simple_buffer<ScrapEngine::Vertex>* ScrapEngine::VulkanSkyboxInstance::getVertexbuffer()
{
	return vertexbuffer;
}

ScrapEngine::simple_buffer<uint32_t>* ScrapEngine::VulkanSkyboxInstance::getIndexbuffer()
{
	return indexbuffer;
}
