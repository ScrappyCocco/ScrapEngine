#pragma once
#include "../Texture/SkyboxTexture.h"
#include "../Texture/TextureImageView.h"
#include "../Texture/TextureSampler.h"
#include "../Buffer/Vertex/VertexBuffer.h"
#include "../Buffer/Index/IndexBuffer.h"
#include "../Model/VulkanModel.h"
#include "../Descriptor/VulkanDescriptorPool.h"
#include "../Descriptor/VulkanDescriptorSet.h"
#include "../Device/VulkanDevice.h"
#include "../SwapChain/VulkanSwapChain.h"
#include "../RenderPass/VulkanRenderPass.h"
#include "../../Utility/UsefulTypes.h"

namespace ScrapEngine {

	class SkyboxTexture;

	class VulkanSkyboxInstance
	{
	private:
		ScrapEngine::VulkanGraphicsPipeline* VulkanRenderGraphicsPipeline = nullptr;
		ScrapEngine::SkyboxTexture* SkyboxTexture = nullptr;
		ScrapEngine::TextureImageView* VulkanTextureImageView = nullptr;
		ScrapEngine::TextureSampler* VulkanTextureSampler = nullptr;
		ScrapEngine::VulkanModel* VulkanRenderModel = nullptr;
		ScrapEngine::VertexBuffer* VulkanRenderVertexBuffer = nullptr;
		ScrapEngine::IndexBuffer* VulkanRenderIndexBuffer = nullptr;
		ScrapEngine::UniformBuffer* VulkanRenderUniformBuffer = nullptr;
		ScrapEngine::VulkanDescriptorPool* VulkanRenderDescriptorPool = nullptr;
		ScrapEngine::VulkanDescriptorSet* VulkanRenderDescriptorSet = nullptr;

		simple_buffer<Vertex>* vertexbuffer = nullptr;
		simple_buffer<uint32_t>* indexbuffer = nullptr;
		ScrapEngine::Transform skyboxTransform;
	public:
		VulkanSkyboxInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::array<std::string, 6>& texture_path,
			ScrapEngine::VulkanDevice* RenderDevice, vk::CommandPool* CommandPool, vk::Queue* graphicsQueue, ScrapEngine::VulkanSwapChain* SwapChain,
			ScrapEngine::VulkanRenderPass* RenderingPass);
		~VulkanSkyboxInstance();

		void updateUniformBuffer(uint32_t currentImage, ScrapEngine::Camera* RenderCamera);
		void deleteGraphicsPipeline();

		int getCubemapSize();
		void setCubemapSize(unsigned int newSize);

		ScrapEngine::UniformBuffer* getVulkanRenderUniformBuffer();
		ScrapEngine::VulkanGraphicsPipeline* getVulkanRenderGraphicsPipeline();
		ScrapEngine::VulkanDescriptorSet* getVulkanRenderDescriptorSet();
		ScrapEngine::simple_buffer<ScrapEngine::Vertex>* getVertexbuffer();
		ScrapEngine::simple_buffer<uint32_t>* getIndexbuffer();
	};

}

