#include <Engine/Rendering/Pipeline/StandardPipeline/StandardVulkanGraphicsPipeline.h>
#include <Engine/Rendering/Shader/ShaderManager.h>
#include <Engine/Rendering/Base/Vertex.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/RenderPass/StandardRenderPass/StandardRenderPass.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::StandardVulkanGraphicsPipeline::StandardVulkanGraphicsPipeline(const char* vertex_shader,
                                                                                    const char* fragment_shader,
                                                                                    vk::Extent2D* swap_chain_extent,
                                                                                    vk::DescriptorSetLayout*
                                                                                    descriptor_set_layout,
                                                                                    vk::SampleCountFlagBits
                                                                                    msaa_samples)
{
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

	//Parameter
	uint32_t enable_pcf = 1;

	vk::SpecializationMapEntry specialization_map_entry(0, 0, sizeof(uint32_t));
	vk::SpecializationInfo specialization_info(1, &specialization_map_entry, sizeof(uint32_t), &enable_pcf);
	shader_stages[1].setPSpecializationInfo(&specialization_info);

	auto attribute_descriptions = Vertex::get_attribute_descriptions();
	auto binding_description = Vertex::get_binding_description();

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
		static_cast<float>(swap_chain_extent->width),
		static_cast<float>(swap_chain_extent->height),
		0.0f,
		1.0f);

	vk::Rect2D scissor(
		vk::Offset2D(),
		*swap_chain_extent
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
		vk::FrontFace::eCounterClockwise
	);
	rasterizer.setLineWidth(1.0f);

	vk::PipelineMultisampleStateCreateInfo multisampling(
		vk::PipelineMultisampleStateCreateFlags(),
		msaa_samples
	);

	vk::PipelineDepthStencilStateCreateInfo depth_stencil(
		vk::PipelineDepthStencilStateCreateFlags(),
		true,
		true,
		vk::CompareOp::eLessOrEqual
	);

	vk::PipelineColorBlendAttachmentState color_blend_attachment;
	color_blend_attachment.setColorWriteMask(
		vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::
		ColorComponentFlagBits::eA);

	vk::PipelineColorBlendStateCreateInfo color_blending(
		vk::PipelineColorBlendStateCreateFlags(),
		false,
		vk::LogicOp::eCopy,
		1,
		&color_blend_attachment
	);

	vk::PipelineLayoutCreateInfo pipeline_layout_info(
		vk::PipelineLayoutCreateFlags(),
		1,
		&(*descriptor_set_layout)
	);

	const vk::Result result_layout = VulkanDevice::get_instance()->get_logical_device()->createPipelineLayout(
		&pipeline_layout_info, nullptr, &pipeline_layout_);

	if (result_layout != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result_layout, "StandardVulkanGraphicsPipeline: Failed to create pipeline layout!");
	}

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
		nullptr,
		pipeline_layout_,
		*StandardRenderPass::get_instance(),
		0
	);

	const vk::Result result = VulkanDevice::get_instance()->get_logical_device()->createGraphicsPipelines(
		nullptr, 1, &pipeline_info, nullptr,
		&graphics_pipeline_);

	if (result != vk::Result::eSuccess)
	{
		Debug::DebugLog::fatal_error(result, "StandardVulkanGraphicsPipeline: Failed to create graphics pipeline!");
	}
}
