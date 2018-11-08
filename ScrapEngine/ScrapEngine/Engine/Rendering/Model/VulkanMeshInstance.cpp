#include "VulkanMeshInstance.h"
#include "../../Debug/DebugLog.h"

ScrapEngine::VulkanMeshInstance::VulkanMeshInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::string& texture_path,
	ScrapEngine::VulkanDevice* RenderDevice, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue, ScrapEngine::VulkanSwapChain* SwapChain, 
	ScrapEngine::VulkanRenderPass* RenderingPass)
{
	vk::Device* device_ref = RenderDevice->getLogicalDevice();
	vk::PhysicalDevice* physical_device_ref = RenderDevice->getPhysicalDevice();
	VulkanRenderDescriptorSet = new VulkanDescriptorSet(device_ref);
	DebugLog::printToConsoleLog("VulkanDescriptorSet created");
	VulkanRenderGraphicsPipeline = new VulkanGraphicsPipeline(vertex_shader_path.c_str(), fragment_shader_path.c_str(), device_ref, &SwapChain->getSwapChainExtent(), RenderingPass->getRenderPass(), VulkanRenderDescriptorSet->getDescriptorSetLayout(), RenderDevice->getMsaaSamples());
	DebugLog::printToConsoleLog("VulkanGraphicsPipeline created");
	VulkanTextureImage = new TextureImage(texture_path, device_ref, physical_device_ref, CommandPool, graphicsQueue);
	DebugLog::printToConsoleLog("TextureImage created");
	VulkanTextureImageView = new TextureImageView(device_ref, VulkanTextureImage->getTextureImage(), VulkanTextureImage->getMipLevels());
	DebugLog::printToConsoleLog("TextureImageView created");
	VulkanTextureSampler = new TextureSampler(device_ref, VulkanTextureImage->getMipLevels());
	DebugLog::printToConsoleLog("TextureSampler created");
	VulkanRenderModel = new VulkanModel(model_path);
	DebugLog::printToConsoleLog("VulkanModel loaded");
	VulkanRenderVertexBuffer = new VertexBuffer(device_ref, physical_device_ref, VulkanRenderModel->getVertices(), CommandPool, graphicsQueue);
	DebugLog::printToConsoleLog("VertexBuffer created");
	VulkanRenderIndexBuffer = new IndexBuffer(device_ref, physical_device_ref, VulkanRenderModel->getIndices(), CommandPool, graphicsQueue);
	DebugLog::printToConsoleLog("IndexBuffer created");
	VulkanRenderUniformBuffer = new UniformBuffer(device_ref, physical_device_ref, SwapChain->getSwapChainImagesVector(), SwapChain->getSwapChainExtent());
	DebugLog::printToConsoleLog("UniformBuffer created");
	VulkanRenderDescriptorPool = new VulkanDescriptorPool(device_ref, SwapChain->getSwapChainImagesVector());
	DebugLog::printToConsoleLog("VulkanDescriptorPool created");
	VulkanRenderDescriptorSet->createDescriptorSets(VulkanRenderDescriptorPool->getDescriptorPool(), SwapChain->getSwapChainImagesVector(), VulkanRenderUniformBuffer->getUniformBuffers(),
		VulkanTextureImageView->getTextureImageView(), VulkanTextureSampler->getTextureSampler());
	DebugLog::printToConsoleLog("(DescriptorSets created)");
	vertexbuffer = new simple_buffer<Vertex>(VulkanRenderVertexBuffer->getVertexBuffer(), VulkanRenderModel->getVertices());
	indexbuffer = new simple_buffer<uint32_t>(VulkanRenderIndexBuffer->getIndexBuffer(), VulkanRenderModel->getIndices());
}

ScrapEngine::VulkanMeshInstance::~VulkanMeshInstance()
{
	delete VulkanTextureSampler;
	delete VulkanTextureImageView;
	delete VulkanTextureImage;
	delete VulkanRenderDescriptorPool;
	delete VulkanRenderDescriptorSet;
	delete VulkanRenderUniformBuffer;
	delete VulkanRenderIndexBuffer;
	delete VulkanRenderVertexBuffer;
	delete VulkanRenderModel;
	//TO CHECK
}

void ScrapEngine::VulkanMeshInstance::setMeshLocation(glm::vec3 location)
{
	object_location.location = location;
}

void ScrapEngine::VulkanMeshInstance::setMeshRotation(glm::vec3 rotation)
{
	object_location.rotation = rotation;
}

void ScrapEngine::VulkanMeshInstance::setMeshScale(glm::vec3 scale)
{
	object_location.scale = scale;
}

glm::vec3 ScrapEngine::VulkanMeshInstance::getMeshLocation()
{
	return object_location.location;
}

glm::vec3 ScrapEngine::VulkanMeshInstance::getMeshRotation()
{
	return object_location.rotation;
}

glm::vec3 ScrapEngine::VulkanMeshInstance::getMeshScale()
{
	return object_location.scale;
}

void ScrapEngine::VulkanMeshInstance::updateUniformBuffer(uint32_t currentImage, ScrapEngine::Camera* RenderCamera)
{
	VulkanRenderUniformBuffer->updateUniformBuffer(currentImage, object_location, RenderCamera);
}

ScrapEngine::UniformBuffer* ScrapEngine::VulkanMeshInstance::getVulkanRenderUniformBuffer()
{
	return VulkanRenderUniformBuffer;
}

ScrapEngine::VulkanGraphicsPipeline* ScrapEngine::VulkanMeshInstance::getVulkanRenderGraphicsPipeline()
{
	return VulkanRenderGraphicsPipeline;
}

ScrapEngine::VulkanDescriptorSet* ScrapEngine::VulkanMeshInstance::getVulkanRenderDescriptorSet()
{
	return VulkanRenderDescriptorSet;
}

ScrapEngine::simple_buffer<ScrapEngine::Vertex>* ScrapEngine::VulkanMeshInstance::getVertexbuffer()
{
	return vertexbuffer;
}

ScrapEngine::simple_buffer<uint32_t>* ScrapEngine::VulkanMeshInstance::getIndexbuffer()
{
	return indexbuffer;
}

void ScrapEngine::VulkanMeshInstance::deleteGraphicsPipeline()
{
	delete VulkanRenderGraphicsPipeline;
}
