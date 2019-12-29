#include <Engine/Rendering/Pipeline/GuiPipeline/GuiVulkanGraphicsPipeline.h>
#include <Engine/Rendering/Shader/ShaderManager.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <imgui.h>

ScrapEngine::Render::GuiVulkanGraphicsPipeline::GuiVulkanGraphicsPipeline(const char* vertex_shader,
                                                                          const char* fragment_shader,
                                                                          vk::DescriptorSetLayout*
                                                                          descriptor_set_layout,
                                                                          size_t block_size,
                                                                          BaseRenderPass* render_pass)
{
	// Pipeline layout
	vk::PushConstantRange push_constant_range;
	push_constant_range.stageFlags = vk::ShaderStageFlagBits::eVertex;
	push_constant_range.offset = 0;
	push_constant_range.setSize(static_cast<uint32_t>(block_size));

	vk::PipelineLayoutCreateInfo pipeline_layout_create_info;
	pipeline_layout_create_info.setPSetLayouts(descriptor_set_layout);
	pipeline_layout_create_info.setSetLayoutCount(1);
	pipeline_layout_create_info.setPushConstantRangeCount(1);
	pipeline_layout_create_info.setPPushConstantRanges(&push_constant_range);

	if (VulkanDevice::get_instance()->get_logical_device()->createPipelineLayout(
			&pipeline_layout_create_info, nullptr, &pipeline_layout_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("GuiVulkanGraphicsPipeline: Failed to create pipeline layout!");
	}

	// Setup graphics pipeline for UI rendering
	vk::PipelineInputAssemblyStateCreateInfo input_assembly(
		vk::PipelineInputAssemblyStateCreateFlags(),
		vk::PrimitiveTopology::eTriangleList,
		false
	);
	vk::PipelineRasterizationStateCreateInfo rasterizer(
		vk::PipelineRasterizationStateCreateFlags(),
		false,
		false,
		vk::PolygonMode::eFill,
		vk::CullModeFlagBits::eNone,
		vk::FrontFace::eCounterClockwise
	);
	rasterizer.setLineWidth(1.0f);

	// Enable blending
	vk::PipelineColorBlendAttachmentState color_blend_attachment;
	color_blend_attachment.blendEnable = true;
	color_blend_attachment.setColorWriteMask(
		vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::
		ColorComponentFlagBits::eA);
	color_blend_attachment.setSrcColorBlendFactor(vk::BlendFactor::eSrcAlpha);
	color_blend_attachment.setDstColorBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha);
	color_blend_attachment.setColorBlendOp(vk::BlendOp::eAdd);
	color_blend_attachment.setSrcAlphaBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha);
	color_blend_attachment.setDstAlphaBlendFactor(vk::BlendFactor::eZero);
	color_blend_attachment.setAlphaBlendOp(vk::BlendOp::eAdd);

	vk::PipelineColorBlendStateCreateInfo color_blending;
	color_blending.setAttachmentCount(1);
	color_blending.setPAttachments(&color_blend_attachment);

	//Load shaders
	vk::ShaderModule vert_shader_module = ShaderManager::get_instance()->get_shader_module(vertex_shader);

	vk::ShaderModule frag_shader_module = ShaderManager::get_instance()->get_shader_module(fragment_shader);

	vk::PipelineShaderStageCreateInfo vert_shader_stage_info(
		vk::PipelineShaderStageCreateFlags(),
		vk::ShaderStageFlagBits::eVertex,
		vert_shader_module,
		"main"
	);

	vk::PipelineShaderStageCreateInfo frag_shader_stage_info(
		vk::PipelineShaderStageCreateFlags(),
		vk::ShaderStageFlagBits::eFragment,
		frag_shader_module,
		"main"
	);

	vk::PipelineShaderStageCreateInfo shader_stages[] = {vert_shader_stage_info, frag_shader_stage_info};

	std::vector<vk::VertexInputBindingDescription> vertex_input_bindings = {
		vk::VertexInputBindingDescription(0, sizeof(ImDrawVert), vk::VertexInputRate::eVertex),
	};

	// Location 0: Position, Location 1: UV, Location 0: Color
	std::vector<vk::VertexInputAttributeDescription> vertex_input_attributes = {
		vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32Sfloat, offsetof(ImDrawVert, pos)),
		vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32Sfloat, offsetof(ImDrawVert, uv)),
		vk::VertexInputAttributeDescription(2, 0, vk::Format::eR8G8B8A8Unorm, offsetof(ImDrawVert, col)),
	};

	vk::PipelineVertexInputStateCreateInfo vertex_input_info(
		vk::PipelineVertexInputStateCreateFlags(),
		static_cast<uint32_t>(vertex_input_bindings.size()),
		vertex_input_bindings.data(),
		static_cast<uint32_t>(vertex_input_attributes.size()),
		vertex_input_attributes.data()
	);

	vk::PipelineViewportStateCreateInfo viewport_state;
	viewport_state.setScissorCount(1);
	viewport_state.setViewportCount(1);

	std::vector<vk::DynamicState> dynamic_state_enables = {
		vk::DynamicState::eViewport,
		vk::DynamicState::eScissor
	};
	vk::PipelineDynamicStateCreateInfo dynamic_state;
	dynamic_state.setDynamicStateCount(static_cast<uint32_t>(dynamic_state_enables.size()));
	dynamic_state.setPDynamicStates(dynamic_state_enables.data());

	vk::PipelineMultisampleStateCreateInfo multisampling(
		vk::PipelineMultisampleStateCreateFlags(),
		VulkanDevice::get_instance()->get_msaa_samples()
	);

	vk::PipelineDepthStencilStateCreateInfo depth_stencil(
		vk::PipelineDepthStencilStateCreateFlags(),
		false,
		false,
		vk::CompareOp::eLessOrEqual
	);

	vk::GraphicsPipelineCreateInfo pipeline_info(
		vk::PipelineCreateFlags(),
		2,
		shader_stages,
		&vertex_input_info,
		&input_assembly,
		nullptr,
		&viewport_state,
		&rasterizer,
		&multisampling,
		&depth_stencil,
		&color_blending,
		&dynamic_state,
		pipeline_layout_,
		*render_pass,
		0
	);

	if (VulkanDevice::get_instance()->get_logical_device()->createGraphicsPipelines(
			nullptr, 1, &pipeline_info, nullptr,
			&graphics_pipeline_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("GuiVulkanGraphicsPipeline: Failed to create graphics pipeline!");
	}
}
