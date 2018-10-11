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
#include "../Buffer/VulkanFrameBuffer.h"
#include "../Command/VulkanCommandPool.h"
#include "../Buffer/VulkanCommandBuffer.h"
#include "../Semaphores/VulkanSemaphoresManager.h"
#include "../Queue/GraphicsQueue.h"
#include "../Queue/PresentQueue.h"
#include "../Buffer/Vertex/VertexBuffer.h"
#include "../Buffer/Index/IndexBuffer.h"
#include "../Buffer/Uniform/UniformBuffer.h"
#include "../Descriptor/VulkanDescriptorSet.h"
#include "../Descriptor/VulkanDescriptorPool.h"
#include "../Texture/TextureImage.h"
#include "../Texture/TextureImageView.h"
#include "../Texture/TextureSampler.h"
#include "../DepthResources/VulkanDepthResources.h"
#include "../Texture/VulkanColorResources.h"
#include "../Model/VulkanModel.h"
#include "../Model/VulkanMeshInstance.h"

namespace ScrapEngine {
	class RenderManager
	{
	private:
		ScrapEngine::GameWindow* GameWindow = nullptr;
		ScrapEngine::VukanInstance* VulkanInstance = nullptr;
		ScrapEngine::VulkanDevice* VulkanRenderDevice = nullptr;
		ScrapEngine::VulkanSwapChain* VulkanRenderSwapChain = nullptr;
		ScrapEngine::VulkanImageView* VulkanRenderImageView = nullptr;
		ScrapEngine::VulkanRenderPass* VulkanRenderingPass = nullptr;
		ScrapEngine::VulkanFrameBuffer* VulkanRenderFrameBuffer = nullptr;
		ScrapEngine::VulkanCommandPool* VulkanRenderCommandPool = nullptr;
		ScrapEngine::VulkanCommandBuffer* VulkanRenderCommandBuffer = nullptr;
		ScrapEngine::GraphicsQueue* VulkanGraphicsQueue = nullptr;
		ScrapEngine::PresentQueue* VulkanPresentationQueue = nullptr;
		ScrapEngine::VulkanSemaphoresManager* VulkanRenderSemaphores = nullptr;
		ScrapEngine::VulkanSurface* VulkanWindowSurface = nullptr;
		ScrapEngine::VulkanDepthResources* VulkanRenderDepth = nullptr;
		ScrapEngine::VulkanColorResources* VulkanRenderColor = nullptr;

		ScrapEngine::Camera* RenderCamera = nullptr;

		std::vector<ScrapEngine::VulkanMeshInstance*> LoadedModels;

		size_t currentFrame = 0;

		vk::Device deviceRef;
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

		ScrapEngine::VulkanMeshInstance* loadMesh(const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& model_path, const std::string& texture_path);
		ScrapEngine::VulkanMeshInstance* loadMesh(const std::string& model_path, const std::string& texture_path);
		void unloadMesh(ScrapEngine::VulkanMeshInstance* meshToUnload);

		ScrapEngine::GameWindow* getGameWindow() const;
		ScrapEngine::Camera* getRenderCamera() const;
	};
}

