#include "VulkanSkyboxInstance.h"

ScrapEngine::Render::VulkanSkyboxInstance::VulkanSkyboxInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::array<std::string, 6>& texture_path,
	ScrapEngine::Render::VulkanDevice* RenderDevice, ScrapEngine::Render::VulkanSwapChain* SwapChain)
{
	VulkanRenderDescriptorSet = new VulkanDescriptorSet();
	Debug::DebugLog::print_to_console_log("VulkanDescriptorSet created");
	VulkanRenderGraphicsPipeline = new VulkanGraphicsPipeline(vertex_shader_path.c_str(), fragment_shader_path.c_str(), &SwapChain->getSwapChainExtent(), VulkanRenderDescriptorSet->getDescriptorSetLayout(), RenderDevice->getMsaaSamples(), true);
	Debug::DebugLog::print_to_console_log("VulkanGraphicsPipeline created");
	SkyboxTexture = new ScrapEngine::Render::SkyboxTexture(texture_path);
	Debug::DebugLog::print_to_console_log("TextureImage created");
	VulkanTextureImageView = new TextureImageView(SkyboxTexture->getTextureImage(), SkyboxTexture->getMipLevels(), true, 6);
	Debug::DebugLog::print_to_console_log("TextureImageView created");
	VulkanTextureSampler = new TextureSampler(SkyboxTexture->getMipLevels(), vk::Filter::eLinear, vk::Filter::eLinear, vk::SamplerMipmapMode::eLinear,
		vk::SamplerAddressMode::eClampToEdge, vk::SamplerAddressMode::eClampToEdge, vk::SamplerAddressMode::eClampToEdge, 
		false, vk::CompareOp::eNever, true, 16, vk::BorderColor::eFloatOpaqueWhite);
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
	VulkanRenderDescriptorSet->createDescriptorSets(VulkanRenderDescriptorPool->getDescriptorPool(), SwapChain->getSwapChainImagesVector(), VulkanRenderUniformBuffer->get_uniform_buffers(),
		VulkanTextureImageView->getTextureImageView(), VulkanTextureSampler->getTextureSampler());
	Debug::DebugLog::print_to_console_log("(DescriptorSets created)");
	vertexbuffer = new simple_buffer<Vertex>(VulkanRenderVertexBuffer->getVertexBuffer(), VulkanRenderModel->getVertices());
	indexbuffer = new simple_buffer<uint32_t>(VulkanRenderIndexBuffer->getIndexBuffer(), VulkanRenderModel->getIndices());
	skyboxTransform.location = glm::vec3(0, 0, 0);
	skyboxTransform.scale = glm::vec3(50, 50, 50);
}

ScrapEngine::Render::VulkanSkyboxInstance::~VulkanSkyboxInstance()
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

void ScrapEngine::Render::VulkanSkyboxInstance::updateUniformBuffer(const uint32_t& currentImage, ScrapEngine::Camera* RenderCamera)
{
	VulkanRenderUniformBuffer->update_uniform_buffer(currentImage, skyboxTransform, RenderCamera);
}

void ScrapEngine::Render::VulkanSkyboxInstance::deleteGraphicsPipeline()
{
	delete VulkanRenderGraphicsPipeline;
}

int ScrapEngine::Render::VulkanSkyboxInstance::getCubemapSize()
{
	return (int)skyboxTransform.scale.x;
}

void ScrapEngine::Render::VulkanSkyboxInstance::setCubemapSize(unsigned int newSize)
{
	skyboxTransform.scale = glm::vec3(newSize, newSize, newSize);
}

ScrapEngine::Render::UniformBuffer* ScrapEngine::Render::VulkanSkyboxInstance::getVulkanRenderUniformBuffer()
{
	return VulkanRenderUniformBuffer;
}

ScrapEngine::Render::VulkanGraphicsPipeline* ScrapEngine::Render::VulkanSkyboxInstance::getVulkanRenderGraphicsPipeline()
{
	return VulkanRenderGraphicsPipeline;
}

ScrapEngine::Render::VulkanDescriptorSet* ScrapEngine::Render::VulkanSkyboxInstance::getVulkanRenderDescriptorSet()
{
	return VulkanRenderDescriptorSet;
}

ScrapEngine::simple_buffer<ScrapEngine::Vertex>* ScrapEngine::Render::VulkanSkyboxInstance::getVertexbuffer()
{
	return vertexbuffer;
}

ScrapEngine::simple_buffer<uint32_t>* ScrapEngine::Render::VulkanSkyboxInstance::getIndexbuffer()
{
	return indexbuffer;
}
