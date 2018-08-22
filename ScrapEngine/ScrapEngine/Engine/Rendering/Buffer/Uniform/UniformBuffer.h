#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <glm/glm.hpp>

namespace ScrapEngine {
	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	class UniformBuffer
	{
	private:
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;

		VkDevice deviceRef;
		size_t swapChainImagesSize;
	public:
		UniformBuffer(VkDevice input_deviceRef, VkPhysicalDevice PhysicalDevice, const std::vector<VkImage>* swapChainImages);
		~UniformBuffer();

		void updateUniformBuffer(uint32_t currentImage, VkExtent2D* swapChainExtent);
		const std::vector<VkBuffer>* getUniformBuffers();
		const std::vector<VkDeviceMemory>* getUniformBuffersMemory();
	};

}

