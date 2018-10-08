#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../../../Utility/UsefulTypes.h"

namespace ScrapEngine {
	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	class UniformBuffer
	{
	private:
		std::vector<vk::Buffer> uniformBuffers;
		std::vector<vk::DeviceMemory> uniformBuffersMemory;

		vk::Device* deviceRef;
		size_t swapChainImagesSize;

		int called = 0;
	public:
		UniformBuffer(vk::Device* input_deviceRef, vk::PhysicalDevice* PhysicalDevice, const std::vector<vk::Image>* swapChainImages);
		~UniformBuffer();

		void updateUniformBuffer(uint32_t currentImage, vk::Extent2D* swapChainExtent, ScrapEngine::Transform object_transform);
		const std::vector<vk::Buffer>* getUniformBuffers();
		const std::vector<vk::DeviceMemory>* getUniformBuffersMemory();
	};

}

