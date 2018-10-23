#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../../../Utility/UsefulTypes.h"
#include "../../Camera/Camera.h"

namespace ScrapEngine {
	struct SkyboxUniformBufferObject {
		glm::mat4 projection;
		glm::mat4 model;
		float lodBias = 0.0f;
	};

	class SkyboxUniformBuffer
	{
	private:
		std::vector<vk::Buffer> uniformBuffers;
		std::vector<vk::DeviceMemory> uniformBuffersMemory;

		vk::Device* deviceRef;
		vk::Extent2D swapChainExtent;
		size_t swapChainImagesSize;
	public:
		SkyboxUniformBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, const std::vector<vk::Image>* swapChainImages, vk::Extent2D input_swapChainExtent);
		~SkyboxUniformBuffer();

		void updateUniformBuffer(uint32_t currentImage, ScrapEngine::Transform object_transform, ScrapEngine::Camera* RenderCamera);
		const std::vector<vk::Buffer>* getUniformBuffers();
		const std::vector<vk::DeviceMemory>* getUniformBuffersMemory();
	};

}

