#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "Engine/Rendering/Buffer/UniformBuffer/UniformBuffer.h"

namespace ScrapEngine {
	namespace Render {
		class VulkanDescriptorSet
		{
		private:
			vk::DescriptorSetLayout descriptorSetLayout;
			vk::PipelineLayout pipelineLayout;
			std::vector<vk::DescriptorSet> descriptorSets;
		public:
			VulkanDescriptorSet();
			~VulkanDescriptorSet();

			void createDescriptorSets(vk::DescriptorPool* descriptorPool, const std::vector<vk::Image>* swapChainImages, const std::vector<vk::Buffer>* uniformBuffers, vk::ImageView* textureImageView, vk::Sampler* textureSampler, const vk::DeviceSize& BufferInfoSize = sizeof(UniformBufferObject));

			vk::DescriptorSetLayout* getDescriptorSetLayout();
			vk::PipelineLayout* getPipelineLayout();
			const std::vector<vk::DescriptorSet>* getDescriptorSets();
		};
	}
}

