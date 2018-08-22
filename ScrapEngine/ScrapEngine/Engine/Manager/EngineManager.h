#pragma once

#include "../Debug/DebugLog.h"

#include "../Rendering/Window/GameWindow.h"
#include "../Rendering/Window/VulkanSurface.h"
#include "../Rendering/Instance/VukanInstance.h"
#include "../Rendering/Device/VulkanDevice.h"
#include "../Rendering/SwapChain/VulkanSwapChain.h"
#include "../Rendering/SwapChain/VulkanImageView.h"
#include "../Rendering/Pipeline/VulkanGraphicsPipeline.h"
#include "../Rendering/RenderPass/VulkanRenderPass.h"
#include "../Rendering/Buffer/VulkanFrameBuffer.h"
#include "../Rendering/Command/VulkanCommandPool.h"
#include "../Rendering/Buffer/VulkanCommandBuffer.h"
#include "../Rendering/Semaphores/VulkanSemaphoresManager.h"
#include "../Rendering/Queue/GraphicsQueue.h"
#include "../Rendering/Queue/PresentQueue.h"
#include "../Rendering/Buffer/Vertex/VertexBuffer.h"
#include "../Rendering/Buffer/Index/IndexBuffer.h"
#include "../Rendering/Buffer/Uniform/UniformBuffer.h"
#include "../Rendering/Descriptor/VulkanDescriptorSet.h"
#include "../Rendering/Descriptor/VulkanDescriptorPool.h"
#include "../Rendering/Texture/TextureImage.h"
#include "../Rendering/Texture/TextureImageView.h"
#include "../Rendering/Texture/TextureSampler.h"
#include "../Rendering/DepthResources/VulkanDepthResources.h"
#include "../Rendering/Texture/VulkanColorResources.h"
#include "../Rendering/Model/VulkanModel.h"

namespace ScrapEngine {

	class EngineManager
	{
	private:
		ScrapEngine::GameWindow* GameWindow = nullptr;
		ScrapEngine::VukanInstance* VulkanInstance = nullptr;
		ScrapEngine::VulkanDevice* VulkanRenderDevice = nullptr;
		ScrapEngine::VulkanSwapChain* VulkanRenderSwapChain = nullptr;
		ScrapEngine::VulkanImageView* VulkanRenderImageView = nullptr;
		ScrapEngine::VulkanGraphicsPipeline* VulkanRenderGraphicsPipeline = nullptr;
		ScrapEngine::VulkanRenderPass* VulkanRenderingPass = nullptr;
		ScrapEngine::VulkanFrameBuffer* VulkanRenderFrameBuffer = nullptr;
		ScrapEngine::VulkanCommandPool* VulkanRenderCommandPool = nullptr;
		ScrapEngine::VulkanCommandBuffer* VulkanRenderCommandBuffer = nullptr;
		ScrapEngine::GraphicsQueue* VulkanGraphicsQueue = nullptr;
		ScrapEngine::PresentQueue* VulkanPresentationQueue = nullptr;
		ScrapEngine::VulkanSemaphoresManager* VulkanRenderSemaphores = nullptr;
		ScrapEngine::VulkanSurface* VulkanWindowSurface = nullptr;
		ScrapEngine::VertexBuffer* VulkanRenderVertexBuffer = nullptr;
		ScrapEngine::IndexBuffer* VulkanRenderIndexBuffer = nullptr;
		ScrapEngine::UniformBuffer* VulkanRenderUniformBuffer = nullptr;
		ScrapEngine::VulkanDescriptorSet* VulkanRenderDescriptorSet = nullptr;
		ScrapEngine::VulkanDescriptorPool* VulkanRenderDescriptorPool = nullptr;
		ScrapEngine::TextureImage* VulkanTextureImage = nullptr;
		ScrapEngine::TextureImageView* VulkanTextureImageView = nullptr;
		ScrapEngine::TextureSampler* VulkanTextureSampler = nullptr;
		ScrapEngine::VulkanDepthResources* VulkanRenderDepth = nullptr;
		ScrapEngine::VulkanColorResources* VulkanRenderColor = nullptr;
		ScrapEngine::VulkanModel* VulkanRenderModel = nullptr;


		struct game_base_info {
			std::string app_name;

			int app_version;
			uint32_t window_WIDTH, window_HEIGHT;
			
			bool window_fullscreen = false;

			game_base_info(std::string input_app_name, int input_app_version, uint32_t input_window_WIDTH, uint32_t input_window_HEIGHT, bool input_window_fullscreen)
				: app_name(input_app_name), app_version(input_app_version), window_WIDTH(input_window_WIDTH), window_HEIGHT(input_window_HEIGHT), window_fullscreen(input_window_fullscreen)
			{}
		};

		game_base_info received_base_game_info;

		bool cleanupDone = false;

		size_t currentFrame = 0;

		VkDevice deviceRef;
		unsigned short int MAX_FRAMES_IN_FLIGHT = 2;
		bool framebufferResized = false;
		const std::vector<VkSemaphore>* imageAvailableSemaphoresRef;
		const std::vector<VkSemaphore>* renderFinishedSemaphoresRef;
		const std::vector<VkFence>* inFlightFencesRef;
	public:
		EngineManager(std::string app_name = "ScrapEngine Game", int app_version = 1, uint32_t window_WIDTH = 800, uint32_t window_HEIGHT = 600, bool fullscreen = false);
		~EngineManager();

		void StartGameLoop();

		ScrapEngine::GameWindow* getGameWindow() const;
	private:
		void initializeEngine();

		void initializeVulkan();

		void createQueues();
		void deleteQueues();

		void mainGameLoop();

		void cleanupEngine();

		void cleanupSwapChain();

		void drawFrame();

		void recreateSwapChain();
	};

}

