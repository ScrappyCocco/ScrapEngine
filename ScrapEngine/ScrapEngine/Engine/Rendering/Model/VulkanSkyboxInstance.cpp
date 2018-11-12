#include "VulkanSkyboxInstance.h"

ScrapEngine::VulkanSkyboxInstance::VulkanSkyboxInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::array<std::string, 6>& texture_path,
	ScrapEngine::VulkanDevice* RenderDevice, ScrapEngine::VulkanSwapChain* SwapChain)
{
	VulkanRenderDescriptorSet = new VulkanDescriptorSet();
	DebugLog::printToConsoleLog("VulkanDescriptorSet created");
	VulkanRenderGraphicsPipeline = new VulkanGraphicsPipeline(vertex_shader_path.c_str(), fragment_shader_path.c_str(), &SwapChain->getSwapChainExtent(), VulkanRenderDescriptorSet->getDescriptorSetLayout(), RenderDevice->getMsaaSamples(), true);
	DebugLog::printToConsoleLog("VulkanGraphicsPipeline created");
	SkyboxTexture = new ScrapEngine::SkyboxTexture(texture_path);
	DebugLog::printToConsoleLog("TextureImage created");
	VulkanTextureImageView = new TextureImageView(SkyboxTexture->getTextureImage(), SkyboxTexture->getMipLevels(), true, 6);
	DebugLog::printToConsoleLog("TextureImageView created");
	VulkanTextureSampler = new TextureSampler(SkyboxTexture->getMipLevels(), vk::Filter::eLinear, vk::Filter::eLinear, vk::SamplerMipmapMode::eLinear,
		vk::SamplerAddressMode::eClampToEdge, vk::SamplerAddressMode::eClampToEdge, vk::SamplerAddressMode::eClampToEdge, 
		false, vk::CompareOp::eNever, true, 16, vk::BorderColor::eFloatOpaqueWhite);
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
	skyboxTransform.location = glm::vec3(0, 0, 0);
	skyboxTransform.scale = glm::vec3(50, 50, 50);
}

ScrapEngine::VulkanSkyboxInstance::~VulkanSkyboxInstance()
{
	delete vertexbuffer;
	delete indexbuffer;
	deleteGraphicsPipeline();
	delete VulkanTextureSampler;
	delete VulkanTextureImageView;
	delete SkyboxTexture;
	delete VulkanRenderDescriptorPool;
	delete VulkanRenderDescriptorSet;
	delete VulkanRenderUniformBuffer;
	delete VulkanRenderIndexBuffer;
	delete VulkanRenderVertexBuffer;
	delete VulkanRenderModel;
}

void ScrapEngine::VulkanSkyboxInstance::updateUniformBuffer(const uint32_t& currentImage, ScrapEngine::Camera* RenderCamera)
{
	VulkanRenderUniformBuffer->updateUniformBuffer(currentImage, skyboxTransform, RenderCamera);
}

void ScrapEngine::VulkanSkyboxInstance::deleteGraphicsPipeline()
{
	delete VulkanRenderGraphicsPipeline;
}

int ScrapEngine::VulkanSkyboxInstance::getCubemapSize()
{
	return (int)skyboxTransform.scale.x;
}

void ScrapEngine::VulkanSkyboxInstance::setCubemapSize(unsigned int newSize)
{
	skyboxTransform.scale = glm::vec3(newSize, newSize, newSize);
}

ScrapEngine::UniformBuffer* ScrapEngine::VulkanSkyboxInstance::getVulkanRenderUniformBuffer()
{
	return VulkanRenderUniformBuffer;
}

ScrapEngine::VulkanGraphicsPipeline* ScrapEngine::VulkanSkyboxInstance::getVulkanRenderGraphicsPipeline()
{
	return VulkanRenderGraphicsPipeline;
}

ScrapEngine::VulkanDescriptorSet* ScrapEngine::VulkanSkyboxInstance::getVulkanRenderDescriptorSet()
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
