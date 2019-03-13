#include "VulkanMeshInstance.h"
#include "../../Debug/DebugLog.h"

ScrapEngine::VulkanMeshInstance::VulkanMeshInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::string& texture_path,
	ScrapEngine::VulkanDevice* RenderDevice, ScrapEngine::VulkanSwapChain* SwapChain)
{
	VulkanRenderDescriptorSet = new VulkanDescriptorSet();
	Debug::DebugLog::print_to_console_log("VulkanDescriptorSet created");
	VulkanRenderGraphicsPipeline = new VulkanGraphicsPipeline(vertex_shader_path.c_str(), fragment_shader_path.c_str(), &SwapChain->getSwapChainExtent(), VulkanRenderDescriptorSet->getDescriptorSetLayout(), RenderDevice->getMsaaSamples());
	Debug::DebugLog::print_to_console_log("VulkanGraphicsPipeline created");
	VulkanTextureImage = new TextureImage(texture_path);
	Debug::DebugLog::print_to_console_log("TextureImage created");
	VulkanTextureImageView = new TextureImageView(VulkanTextureImage->getTextureImage(), VulkanTextureImage->getMipLevels());
	Debug::DebugLog::print_to_console_log("TextureImageView created");
	VulkanTextureSampler = new TextureSampler(VulkanTextureImage->getMipLevels());
	Debug::DebugLog::print_to_console_log("TextureSampler created");
	VulkanRenderModel = new VulkanModel(model_path);
	Debug::DebugLog::print_to_console_log("VulkanModel loaded");
	VulkanRenderVertexBuffer = new VertexBuffer(VulkanRenderModel->getVertices());
	Debug::DebugLog::print_to_console_log("VertexBuffer created");
	VulkanRenderIndexBuffer = new IndexBuffer(VulkanRenderModel->getIndices());
	Debug::DebugLog::print_to_console_log("IndexBuffer created");
	VulkanRenderUniformBuffer = new UniformBuffer(SwapChain->getSwapChainImagesVector(), SwapChain->getSwapChainExtent());
	Debug::DebugLog::print_to_console_log("UniformBuffer created");
	VulkanRenderDescriptorPool = new VulkanDescriptorPool(SwapChain->getSwapChainImagesVector());
	Debug::DebugLog::print_to_console_log("VulkanDescriptorPool created");
	VulkanRenderDescriptorSet->createDescriptorSets(VulkanRenderDescriptorPool->getDescriptorPool(), SwapChain->getSwapChainImagesVector(), VulkanRenderUniformBuffer->getUniformBuffers(),
		VulkanTextureImageView->getTextureImageView(), VulkanTextureSampler->getTextureSampler());
	Debug::DebugLog::print_to_console_log("(DescriptorSets created)");
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
