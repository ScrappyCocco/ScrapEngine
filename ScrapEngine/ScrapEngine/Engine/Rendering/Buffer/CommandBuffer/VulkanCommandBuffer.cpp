#include "VulkanCommandBuffer.h"
#include "Engine/Rendering/Base/StaticTypes.h"

ScrapEngine::Render::VulkanCommandBuffer::VulkanCommandBuffer(
	ScrapEngine::Render::VulkanFrameBuffer* swap_chain_frame_buffer, vk::Extent2D* input_swap_chain_extent_ref,
	std::vector<ScrapEngine::Render::VulkanGraphicsPipeline*> input_vulkan_pipeline_ref,
	const std::vector<const std::vector<vk::DescriptorSet>*>& descriptor_sets,
	std::vector<simple_buffer<Vertex>*> vertex_buffer, std::vector<simple_buffer<uint32_t>*> index_buffer
	, ScrapEngine::Render::VulkanSkyboxInstance* SkyboxRef)
{
	const std::vector<vk::Framebuffer>* swap_chain_framebuffers = swap_chain_frame_buffer->
		get_swap_chain_framebuffers_vector();
	command_buffers_.resize(swap_chain_framebuffers->size());

	vk::CommandBufferAllocateInfo allocInfo(
		*VulkanCommandPool::static_command_pool_ref,
		vk::CommandBufferLevel::ePrimary,
		static_cast<uint32_t>(command_buffers_.size())
	);

	if (VulkanDevice::static_logic_device_ref->allocateCommandBuffers(&allocInfo, command_buffers_.data()) != vk::Result::
		eSuccess)
	{
		throw std::runtime_error("VulkanCommandBuffer: Failed to allocate command buffers!");
	}

	for (size_t i = 0; i < command_buffers_.size(); i++)
	{
		vk::CommandBufferBeginInfo begin_info(vk::CommandBufferUsageFlagBits::eSimultaneousUse);

		if (command_buffers_[i].begin(&begin_info) != vk::Result::eSuccess)
		{
			throw std::runtime_error("VulkanCommandBuffer: Failed to begin recording command buffer!");
		}

		vk::RenderPassBeginInfo renderPassInfo(
			*VulkanRenderPass::StaticRenderPassRef,
			(*swap_chain_framebuffers)[i],
			vk::Rect2D(vk::Offset2D(), *input_swap_chain_extent_ref)
		);

		std::array<vk::ClearValue, 2> clearValues = {
			vk::ClearValue(vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f})),
			vk::ClearDepthStencilValue(1.0f, 0)
		};
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		command_buffers_[i].beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);

		vk::DeviceSize offsets[] = {0};

		//Skybox render, must be before the rest of the render
		if (SkyboxRef)
		{
			command_buffers_[i].bindPipeline(vk::PipelineBindPoint::eGraphics,
			                                 *SkyboxRef->getVulkanRenderGraphicsPipeline()->getGraphicsPipeline());
			vk::Buffer buff[] = {*SkyboxRef->getVertexbuffer()->buffer};
			command_buffers_[i].bindVertexBuffers(0, 1, buff, offsets);
			command_buffers_[i].bindIndexBuffer(*SkyboxRef->getIndexbuffer()->buffer, 0, vk::IndexType::eUint32);
			command_buffers_[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
			                                       *SkyboxRef->getVulkanRenderGraphicsPipeline()->getPipelineLayout(),
			                                       0, 1, &(*SkyboxRef
			                                                ->getVulkanRenderDescriptorSet()->get_descriptor_sets())[i],
			                                       0, nullptr);
			command_buffers_[i].drawIndexed(static_cast<uint32_t>((*SkyboxRef->getIndexbuffer()).vectorData->size()), 1,
			                                0, 0, 0);
		}
		//Scene render
		for (int k = 0; k < vertex_buffer.size(); k++)
		{
			command_buffers_[i].bindPipeline(vk::PipelineBindPoint::eGraphics,
			                                 *input_vulkan_pipeline_ref[k]->getGraphicsPipeline());

			vk::Buffer vertex_buffers[] = {*(*vertex_buffer[k]).buffer};

			command_buffers_[i].bindVertexBuffers(0, 1, vertex_buffers, offsets);

			command_buffers_[i].bindIndexBuffer(*(*index_buffer[k]).buffer, 0, vk::IndexType::eUint32);

			command_buffers_[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
			                                       *input_vulkan_pipeline_ref[k]->getPipelineLayout(), 0, 1,
			                                       &(*descriptor_sets[k])[i], 0, nullptr);

			command_buffers_[i].drawIndexed(static_cast<uint32_t>((*index_buffer[k]).vectorData->size()), 1, 0, 0, 0);
		}

		command_buffers_[i].endRenderPass();

		command_buffers_[i].end();
	}
}

ScrapEngine::Render::VulkanCommandBuffer::~VulkanCommandBuffer()
{
	free_command_buffers();
}

void ScrapEngine::Render::VulkanCommandBuffer::free_command_buffers()
{
	VulkanDevice::static_logic_device_ref->freeCommandBuffers(*VulkanCommandPool::static_command_pool_ref,
	                                                       static_cast<uint32_t>(command_buffers_.size()),
	                                                       command_buffers_.data());
	command_buffers_.clear();
}

const std::vector<vk::CommandBuffer>* ScrapEngine::Render::VulkanCommandBuffer::get_command_buffers_vector() const
{
	return &command_buffers_;
}
