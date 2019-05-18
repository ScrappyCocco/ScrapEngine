#pragma once
#include "../../Debug/DebugLog.h"

#include "../../Utility/UsefulTypes.h"
#include "../Window/GameWindow.h"
#include "../Window/VulkanSurface.h"
#include "../Instance/VukanInstance.h"
#include "../Device/VulkanDevice.h"
#include "../SwapChain/VulkanSwapChain.h"
#include "../SwapChain/VulkanImageView.h"
#include "../Pipeline/VulkanGraphicsPipeline.h"
#include "../RenderPass/VulkanRenderPass.h"
#include "Engine/Rendering/Buffer/FrameBuffer/VulkanFrameBuffer.h"
#include "../Command/VulkanCommandPool.h"
#include "Engine/Rendering/Buffer/CommandBuffer/VulkanCommandBuffer.h"
#include "../Semaphores/VulkanSemaphoresManager.h"
#include "../Queue/GraphicsQueue.h"
#include "../Queue/PresentQueue.h"
#include "Engine/Rendering/Buffer/VertexBuffer/VertexBuffer.h"
#include "Engine/Rendering/Buffer/IndexBuffer/IndexBuffer.h"
#include "Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h"
#include "../Descriptor/VulkanDescriptorSet.h"
#include "../Descriptor/VulkanDescriptorPool.h"
#include "../Texture/TextureImage.h"
#include "../Texture/TextureImageView.h"
#include "../Texture/TextureSampler.h"
#include "../DepthResources/VulkanDepthResources.h"
#include "../Texture/VulkanColorResources.h"
#include "../Model/VulkanModel.h"
#include "../Model/VulkanMeshInstance.h"
#include "../Model/VulkanSkyboxInstance.h"

namespace ScrapEngine {
	namespace Render {
		class RenderManager
		{
		private:
			ScrapEngine::Render::GameWindow* GameWindow = nullptr;
			ScrapEngine::Render::VukanInstance* VulkanInstance = nullptr;
			ScrapEngine::Render::VulkanDevice* VulkanRenderDevice = nullptr;
			ScrapEngine::Render::VulkanSwapChain* VulkanRenderSwapChain = nullptr;
			ScrapEngine::Render::VulkanImageView* VulkanRenderImageView = nullptr;
			ScrapEngine::Render::VulkanRenderPass* VulkanRenderingPass = nullptr;
			ScrapEngine::Render::VulkanFrameBuffer* VulkanRenderFrameBuffer = nullptr;
			ScrapEngine::Render::VulkanCommandPool* VulkanRenderCommandPool = nullptr;
			ScrapEngine::Render::VulkanCommandBuffer* VulkanRenderCommandBuffer = nullptr;
			ScrapEngine::Render::GraphicsQueue* VulkanGraphicsQueue = nullptr;
			ScrapEngine::Render::PresentQueue* VulkanPresentationQueue = nullptr;
			ScrapEngine::Render::VulkanSemaphoresManager* VulkanRenderSemaphores = nullptr;
			ScrapEngine::Render::VulkanSurface* VulkanWindowSurface = nullptr;
			ScrapEngine::Render::VulkanDepthResources* VulkanRenderDepth = nullptr;
			ScrapEngine::Render::VulkanColorResources* VulkanRenderColor = nullptr;

			ScrapEngine::Render::Camera* RenderCamera = nullptr;
			ScrapEngine::Render::Camera* defaultCamera = nullptr;

			ScrapEngine::Render::VulkanSkyboxInstance* Skybox = nullptr;

			std::vector<ScrapEngine::Render::VulkanMeshInstance*> LoadedModels;

			size_t currentFrame = 0;
			uint32_t imageIndex;
			vk::Result result;

			unsigned short int MAX_FRAMES_IN_FLIGHT = 2;
			bool framebufferResized = false;
			const std::vector<vk::Semaphore>* imageAvailableSemaphoresRef;
			const std::vector<vk::Semaphore>* renderFinishedSemaphoresRef;
			const std::vector<vk::Fence>* inFlightFencesRef;
		public:
			RenderManager(const ScrapEngine::game_base_info* received_base_game_info);
			~RenderManager();
		private:
			void initializeVulkan(const ScrapEngine::game_base_info* received_base_game_info);

			void createQueues();
			void deleteQueues();

			void createCommandBuffers();
			void deleteCommandBuffers();

			void cleanupSwapChain();
			void recreateSwapChain();

			void createCamera();
		public:
			void drawFrame();
			void waitDeviceIdle();

			//3D mesh and scene stuff
			ScrapEngine::Render::VulkanMeshInstance* loadMesh(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::string& texture_path);
			ScrapEngine::Render::VulkanMeshInstance* loadMesh(const std::string& model_path, const std::string& texture_path);
			void unloadMesh(ScrapEngine::Render::VulkanMeshInstance* meshToUnload);
			ScrapEngine::Render::VulkanSkyboxInstance* loadSkybox(const std::array<std::string, 6>& files_path);

			//User-Window stuff
			ScrapEngine::Render::GameWindow* getGameWindow() const;

			//View-Camera stuff
			ScrapEngine::Render::Camera* getRenderCamera() const;
			ScrapEngine::Render::Camera* getDefaultRenderCamera() const;
			void setRenderCamera(ScrapEngine::Render::Camera* newCamera);
		};
	}
}

