#include <Engine/Rendering/Pipeline/ShadowmappingPipeline/ShadowmappingPipeline.h>
#include <Engine/Rendering/Shader/ShaderManager.h>
#include <Engine/Rendering/Base/Vertex.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/RenderPass/StandardRenderPass/StandardRenderPass.h>

ScrapEngine::Render::ShadowmappingPipeline::ShadowmappingPipeline(const char* vertex_shader,
                                                                  vk::DescriptorSetLayout* descriptor_set_layout,
                                                                  vk::Extent2D* shadowmapping_extent,
                                                                  BaseRenderPass* render_pass)
{
	vk::ShaderModule vert_shader_module = ShaderManager::get_instance()->get_shader_module(vertex_shader);

	vk::PipelineShaderStageCreateInfo vert_shader_stage_info(
		vk::PipelineShaderStageCreateFlags(),
		vk::ShaderStageFlagBits::eVertex,
		vert_shader_module,
		"main"
	);

	vk::PipelineShaderStageCreateInfo shader_stages[] = {vert_shader_stage_info};

	auto attribute_descriptions = OffscreenVertex::get_attribute_descriptions();
	auto binding_description = OffscreenVertex::get_binding_description();

	vk::PipelineVertexInputStateCreateInfo vertex_input_info(
		vk::PipelineVertexInputStateCreateFlags(),
		1,
		&binding_description,
		static_cast<uint32_t>(attribute_descriptions.size()),
		attribute_descriptions.data()
	);

	vk::PipelineInputAssemblyStateCreateInfo input_assembly(
		vk::PipelineInputAssemblyStateCreateFlags(),
		vk::PrimitiveTopology::eTriangleList,
		false
	);

	vk::Viewport viewport(
		0,
		0,
		static_cast<float>(shadowmapping_extent->width),
		static_cast<float>(shadowmapping_extent->height),
		0.0f,
		1.0f
	);

	vk::Rect2D scissor(
		vk::Offset2D(),
		*shadowmapping_extent
	);

	vk::PipelineViewportStateCreateInfo viewport_state(
		vk::PipelineViewportStateCreateFlags(),
		1,
		&viewport,
		1,
		&scissor
	);

	vk::PipelineRasterizationStateCreateInfo rasterizer(
		vk::PipelineRasterizationStateCreateFlags(),
		false,
		false,
		vk::PolygonMode::eFill,
		vk::CullModeFlagBits::eBack,
		vk::FrontFace::eCounterClockwise,
		true
	);
	rasterizer.setLineWidth(1.0f);

	vk::PipelineMultisampleStateCreateInfo multisampling(
		vk::PipelineMultisampleStateCreateFlags(),
		vk::SampleCountFlagBits::e1
	);

	vk::PipelineDepthStencilStateCreateInfo depth_stencil(
		vk::PipelineDepthStencilStateCreateFlags(),
		true,
		true,
		vk::CompareOp::eLessOrEqual
	);

	std::vector<vk::DynamicState> dynamic_states_enable;
	dynamic_states_enable.push_back(vk::DynamicState::eViewport);
	dynamic_states_enable.push_back(vk::DynamicState::eScissor);
	dynamic_states_enable.push_back(vk::DynamicState::eDepthBias);

	vk::PipelineDynamicStateCreateInfo dynamic_state_create_info(
		vk::PipelineDynamicStateCreateFlags(),
		static_cast<uint32_t>(dynamic_states_enable.size()),
		dynamic_states_enable.data()
	);

	//Empty
	vk::PipelineColorBlendStateCreateInfo color_blending;
	color_blending.setAttachmentCount(0);

	vk::PipelineLayoutCreateInfo pipeline_layout_info(
		vk::PipelineLayoutCreateFlags(),
		1,
		&(*descriptor_set_layout)
	);

	if (VulkanDevice::get_instance()->get_logical_device()->createPipelineLayout(
			&pipeline_layout_info, nullptr, &pipeline_layout_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("ShadowmappingPipeline: Failed to create pipeline layout!");
	}

	vk::GraphicsPipelineCreateInfo pipeline_info(
		vk::PipelineCreateFlags(),
		1,
		shader_stages,
		&vertex_input_info,
		&input_assembly,
		nullptr,
		&viewport_state,
		&rasterizer,
		&multisampling,
		&depth_stencil,
		&color_blending,
		&dynamic_state_create_info,
		pipeline_layout_,
		*render_pass,
		0
	);

	if (VulkanDevice::get_instance()->get_logical_device()->createGraphicsPipelines(nullptr, 1, &pipeline_info, nullptr,
	                                                                                &graphics_pipeline_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("StandardVulkanGraphicsPipeline: Failed to create graphics pipeline!");
	}
}
