#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "../../../Utility/UsefulTypes.h"
#include "../../Camera/Camera.h"

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
		std::vector<void*> mappedMemory;

		vk::Extent2D swapChainExtent;
		size_t swapChainImagesSize;
	public:
		UniformBuffer(const std::vector<vk::Image>* swapChainImages, const vk::Extent2D& input_swapChainExtent);
		~UniformBuffer();

		void updateUniformBuffer(const uint32_t& currentImage, const ScrapEngine::Transform& object_transform, ScrapEngine::Camera* RenderCamera);
		const std::vector<vk::Buffer>* getUniformBuffers();
		const std::vector<vk::DeviceMemory>* getUniformBuffersMemory();
	};

}

