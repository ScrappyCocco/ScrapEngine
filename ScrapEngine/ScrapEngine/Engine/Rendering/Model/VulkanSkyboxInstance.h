#pragma once
#include "../Texture/SkyboxTexture.h"
#include "../Texture/TextureImageView.h"
#include "../Texture/TextureSampler.h"
#include "Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h"
#include "Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h"
#include "../Model/VulkanModel.h"
#include "../Descriptor/VulkanDescriptorPool.h"
#include "../Descriptor/VulkanDescriptorSet.h"
#include "../Device/VulkanDevice.h"
#include "../SwapChain/VulkanSwapChain.h"
#include "../RenderPass/VulkanRenderPass.h"
#include "../../Utility/UsefulTypes.h"

namespace ScrapEngine {
	namespace Render {
		class SkyboxTexture;

		class VulkanSkyboxInstance
		{
		private:
			ScrapEngine::Render::VulkanGraphicsPipeline* VulkanRenderGraphicsPipeline = nullptr;
			ScrapEngine::Render::SkyboxTexture* SkyboxTexture = nullptr;
			ScrapEngine::Render::TextureImageView* VulkanTextureImageView = nullptr;
			ScrapEngine::Render::TextureSampler* VulkanTextureSampler = nullptr;
			ScrapEngine::Render::VulkanModel* VulkanRenderModel = nullptr;
			ScrapEngine::Render::VertexBuffer* VulkanRenderVertexBuffer = nullptr;
			ScrapEngine::Render::IndexBuffer* VulkanRenderIndexBuffer = nullptr;
			ScrapEngine::Render::UniformBuffer* VulkanRenderUniformBuffer = nullptr;
			ScrapEngine::Render::VulkanDescriptorPool* VulkanRenderDescriptorPool = nullptr;
			ScrapEngine::Render::VulkanDescriptorSet* VulkanRenderDescriptorSet = nullptr;

			simple_buffer<Vertex>* vertexbuffer = nullptr;
			simple_buffer<uint32_t>* indexbuffer = nullptr;
			ScrapEngine::Transform skyboxTransform;
		public:
			VulkanSkyboxInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::array<std::string, 6>& texture_path,
				ScrapEngine::Render::VulkanDevice* RenderDevice, ScrapEngine::Render::VulkanSwapChain* SwapChain);
			~VulkanSkyboxInstance();

			void updateUniformBuffer(const uint32_t& currentImage, ScrapEngine::Render::Camera* RenderCamera);
			void deleteGraphicsPipeline();

			int getCubemapSize();
			void setCubemapSize(unsigned int newSize);

			ScrapEngine::Render::UniformBuffer* getVulkanRenderUniformBuffer();
			ScrapEngine::Render::VulkanGraphicsPipeline* getVulkanRenderGraphicsPipeline();
			ScrapEngine::Render::VulkanDescriptorSet* getVulkanRenderDescriptorSet();
			ScrapEngine::simple_buffer<ScrapEngine::Vertex>* getVertexbuffer();
			ScrapEngine::simple_buffer<uint32_t>* getIndexbuffer();
		};
	}
}

