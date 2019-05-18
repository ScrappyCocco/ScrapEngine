#pragma once
#include "../Texture/TextureImage.h"
#include "../Texture/TextureImageView.h"
#include "../Texture/TextureSampler.h"
#include "Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h"
#include "Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h"
#include "Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h"
#include "../Model/VulkanModel.h"
#include "Engine/Rendering/Buffer/CommandBuffer/VulkanCommandBuffer.h"
#include "../Descriptor/VulkanDescriptorPool.h"
#include "../Descriptor/VulkanDescriptorSet.h"
#include "../Device/VulkanDevice.h"
#include "../SwapChain/VulkanSwapChain.h"
#include "../RenderPass/VulkanRenderPass.h"
#include "Engine/Rendering/Buffer/FrameBuffer/VulkanFrameBuffer.h"
#include "../../Utility/UsefulTypes.h"

namespace ScrapEngine {
	namespace Render {
		class VulkanMeshInstance
		{
		private:
			ScrapEngine::Render::VulkanGraphicsPipeline* VulkanRenderGraphicsPipeline = nullptr;
			ScrapEngine::Render::TextureImage* VulkanTextureImage = nullptr;
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

			ScrapEngine::Transform object_location;
		public:
			VulkanMeshInstance(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::string& texture_path,
				ScrapEngine::Render::VulkanDevice* RenderDevice, ScrapEngine::Render::VulkanSwapChain* SwapChain);
			~VulkanMeshInstance();

			void setMeshLocation(const glm::vec3& location);
			void setMeshRotation(const glm::vec3& rotation);
			void setMeshScale(const glm::vec3& scale);

			glm::vec3 getMeshLocation() const;
			glm::vec3 getMeshRotation() const;
			glm::vec3 getMeshScale() const;

			void updateUniformBuffer(const uint32_t& currentImage, ScrapEngine::Camera* RenderCamera);
			void deleteGraphicsPipeline();

			ScrapEngine::Render::UniformBuffer* getVulkanRenderUniformBuffer();
			ScrapEngine::Render::VulkanGraphicsPipeline* getVulkanRenderGraphicsPipeline();
			ScrapEngine::Render::VulkanDescriptorSet* getVulkanRenderDescriptorSet();
			ScrapEngine::simple_buffer<ScrapEngine::Vertex>* getVertexbuffer();
			ScrapEngine::simple_buffer<uint32_t>* getIndexbuffer();
		};
	}

}

