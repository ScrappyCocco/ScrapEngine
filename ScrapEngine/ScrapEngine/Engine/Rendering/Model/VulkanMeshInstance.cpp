#include "VulkanMeshInstance.h"
#include "../../Debug/DebugLog.h"

ScrapEngine::Render::VulkanMeshInstance::VulkanMeshInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::string& texture_path,
	ScrapEngine::Render::VulkanDevice* RenderDevice, ScrapEngine::Render::VulkanSwapChain* SwapChain)
{
	VulkanRenderDescriptorSet = new VulkanDescriptorSet();
	Debug::DebugLog::print_to_console_log("VulkanDescriptorSet created");
	VulkanRenderGraphicsPipeline = new VulkanGraphicsPipeline(vertex_shader_path.c_str(), fragment_shader_path.c_str(), &SwapChain->getSwapChainExtent(), VulkanRenderDescriptorSet->get_descriptor_set_layout(), RenderDevice->get_msaa_samples());
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
	VulkanRenderDescriptorSet->create_descriptor_sets(VulkanRenderDescriptorPool->get_descriptor_pool(), SwapChain->getSwapChainImagesVector(), VulkanRenderUniformBuffer->get_uniform_buffers(),
		VulkanTextureImageView->getTextureImageView(), VulkanTextureSampler->getTextureSampler());
	Debug::DebugLog::print_to_console_log("(DescriptorSets created)");
	vertexbuffer = new simple_buffer<Vertex>(VulkanRenderVertexBuffer->get_vertex_buffer(), VulkanRenderModel->getVertices());
	indexbuffer = new simple_buffer<uint32_t>(VulkanRenderIndexBuffer->get_index_buffer(), VulkanRenderModel->getIndices());
}

ScrapEngine::Render::VulkanMeshInstance::~VulkanMeshInstance()
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

void ScrapEngine::Render::VulkanMeshInstance::setMeshLocation(const glm::vec3& location)
{
	object_location.location = location;
}

void ScrapEngine::Render::VulkanMeshInstance::setMeshRotation(const glm::vec3& rotation)
{
	object_location.rotation = rotation;
}

void ScrapEngine::Render::VulkanMeshInstance::setMeshScale(const glm::vec3& scale)
{
	object_location.scale = scale;
}

glm::vec3 ScrapEngine::Render::VulkanMeshInstance::getMeshLocation() const
{
	return object_location.location;
}

glm::vec3 ScrapEngine::Render::VulkanMeshInstance::getMeshRotation() const
{
	return object_location.rotation;
}

glm::vec3 ScrapEngine::Render::VulkanMeshInstance::getMeshScale() const
{
	return object_location.scale;
}

void ScrapEngine::Render::VulkanMeshInstance::updateUniformBuffer(const uint32_t& currentImage, ScrapEngine::Render::Camera* RenderCamera)
{
	VulkanRenderUniformBuffer->update_uniform_buffer(currentImage, object_location, RenderCamera);
}

ScrapEngine::Render::UniformBuffer* ScrapEngine::Render::VulkanMeshInstance::getVulkanRenderUniformBuffer()
{
	return VulkanRenderUniformBuffer;
}

ScrapEngine::Render::VulkanGraphicsPipeline* ScrapEngine::Render::VulkanMeshInstance::getVulkanRenderGraphicsPipeline()
{
	return VulkanRenderGraphicsPipeline;
}

ScrapEngine::Render::VulkanDescriptorSet* ScrapEngine::Render::VulkanMeshInstance::getVulkanRenderDescriptorSet()
{
	return VulkanRenderDescriptorSet;
}

ScrapEngine::simple_buffer<ScrapEngine::Vertex>* ScrapEngine::Render::VulkanMeshInstance::getVertexbuffer()
{
	return vertexbuffer;
}

ScrapEngine::simple_buffer<uint32_t>* ScrapEngine::Render::VulkanMeshInstance::getIndexbuffer()
{
	return indexbuffer;
}

void ScrapEngine::Render::VulkanMeshInstance::deleteGraphicsPipeline()
{
	delete VulkanRenderGraphicsPipeline;
	VulkanRenderGraphicsPipeline = nullptr;
}
