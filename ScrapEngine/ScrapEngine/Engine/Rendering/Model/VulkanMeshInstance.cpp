#include "VulkanMeshInstance.h"
#include "../../Debug/DebugLog.h"

ScrapEngine::VulkanMeshInstance::VulkanMeshInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::string& texture_path,
	ScrapEngine::VulkanDevice* RenderDevice, ScrapEngine::VulkanSwapChain* SwapChain)
{
	VulkanRenderDescriptorSet = new VulkanDescriptorSet();
	DebugLog::printToConsoleLog("VulkanDescriptorSet created");
	VulkanRenderGraphicsPipeline = new VulkanGraphicsPipeline(vertex_shader_path.c_str(), fragment_shader_path.c_str(), &SwapChain->getSwapChainExtent(), VulkanRenderDescriptorSet->getDescriptorSetLayout(), RenderDevice->getMsaaSamples());
	DebugLog::printToConsoleLog("VulkanGraphicsPipeline created");
	VulkanTextureImage = new TextureImage(texture_path);
	DebugLog::printToConsoleLog("TextureImage created");
	VulkanTextureImageView = new TextureImageView(VulkanTextureImage->getTextureImage(), VulkanTextureImage->getMipLevels());
	DebugLog::printToConsoleLog("TextureImageView created");
	VulkanTextureSampler = new TextureSampler(VulkanTextureImage->getMipLevels());
	DebugLog::printToConsoleLog("TextureSampler created");
	VulkanRenderModel = new VulkanModel(model_path);
	DebugLog::printToConsoleLog("VulkanModel loaded");
	VulkanRenderVertexBuffer = new VertexBuffer(VulkanRenderModel->getVertices());
	DebugLog::printToConsoleLog("VertexBuffer created");
	VulkanRenderIndexBuffer = new IndexBuffer(VulkanRenderModel->getIndices());
	DebugLog::printToConsoleLog("IndexBuffer created");
	VulkanRenderUniformBuffer = new UniformBuffer(SwapChain->getSwapChainImagesVector(), SwapChain->getSwapChainExtent());
	DebugLog::printToConsoleLog("UniformBuffer created");
	VulkanRenderDescriptorPool = new VulkanDescriptorPool(SwapChain->getSwapChainImagesVector());
	DebugLog::printToConsoleLog("VulkanDescriptorPool created");
	VulkanRenderDescriptorSet->createDescriptorSets(VulkanRenderDescriptorPool->getDescriptorPool(), SwapChain->getSwapChainImagesVector(), VulkanRenderUniformBuffer->getUniformBuffers(),
		VulkanTextureImageView->getTextureImageView(), VulkanTextureSampler->getTextureSampler());
	DebugLog::printToConsoleLog("(DescriptorSets created)");
	vertexbuffer = new simple_buffer<Vertex>(VulkanRenderVertexBuffer->getVertexBuffer(), VulkanRenderModel->getVertices());
	indexbuffer = new simple_buffer<uint32_t>(VulkanRenderIndexBuffer->getIndexBuffer(), VulkanRenderModel->getIndices());
}

ScrapEngine::VulkanMeshInstance::~VulkanMeshInstance()
{
	delete vertexbuffer;
	delete indexbuffer;
	deleteGraphicsPipeline();
	delete VulkanTextureSampler;
	delete VulkanTextureImageView;
	delete VulkanTextureImage;
	delete VulkanRenderDescriptorPool;
	delete VulkanRenderDescriptorSet;
	delete VulkanRenderUniformBuffer;
	delete VulkanRenderIndexBuffer;
	delete VulkanRenderVertexBuffer;
	delete VulkanRenderModel;
}

void ScrapEngine::VulkanMeshInstance::setMeshLocation(const glm::vec3& location)
{
	object_location.location = location;
}

void ScrapEngine::VulkanMeshInstance::setMeshRotation(const glm::vec3& rotation)
{
	object_location.rotation = rotation;
}

void ScrapEngine::VulkanMeshInstance::setMeshScale(const glm::vec3& scale)
{
	object_location.scale = scale;
}

glm::vec3 ScrapEngine::VulkanMeshInstance::getMeshLocation() const
{
	return object_location.location;
}

glm::vec3 ScrapEngine::VulkanMeshInstance::getMeshRotation() const
{
	return object_location.rotation;
}

glm::vec3 ScrapEngine::VulkanMeshInstance::getMeshScale() const
{
	return object_location.scale;
}

void ScrapEngine::VulkanMeshInstance::updateUniformBuffer(const uint32_t& currentImage, ScrapEngine::Camera* RenderCamera)
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
	VulkanRenderGraphicsPipeline = nullptr;
}
