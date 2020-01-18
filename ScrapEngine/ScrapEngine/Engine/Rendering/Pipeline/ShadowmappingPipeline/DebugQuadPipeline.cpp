#include <Engine/Rendering/Pipeline/ShadowmappingPipeline/DebugQuadPipeline.h>
#include <Engine/Rendering/Shader/ShaderManager.h>
#include <Engine/Rendering/Device/VulkanDevice.h>
#include <Engine/Rendering/RenderPass/StandardRenderPass/StandardRenderPass.h>

ScrapEngine::Render::DebugQuadPipeline::DebugQuadPipeline(const char* vertex_shader, const char* fragment_shader,
                                                          vk::PipelineLayout* quad_layout,
                                                          vk::Extent2D* swap_chain_extent)
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

	//Empty
	vk::PipelineVertexInputStateCreateInfo vertex_input_info;

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
		vk::CullModeFlagBits::eNone,
		vk::FrontFace::eCounterClockwise
	);
	rasterizer.setLineWidth(1.0f);

	vk::PipelineMultisampleStateCreateInfo multisampling(
		vk::PipelineMultisampleStateCreateFlags(),
		StandardRenderPass::get_instance()->get_msaa_samples()
	);

	vk::PipelineDepthStencilStateCreateInfo depth_stencil(
		vk::PipelineDepthStencilStateCreateFlags(),
		true,
		true,
		vk::CompareOp::eLessOrEqual
	);

	//Empty?
	vk::PipelineColorBlendAttachmentState color_blend_attachment;

	vk::PipelineColorBlendStateCreateInfo color_blending(
		vk::PipelineColorBlendStateCreateFlags(),
		false,
		vk::LogicOp::eCopy,
		1,
		&color_blend_attachment
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
		nullptr,
		*quad_layout,
		*StandardRenderPass::get_instance(),
		0
	);

	if (VulkanDevice::get_instance()->get_logical_device()->createGraphicsPipelines(nullptr, 1, &pipeline_info, nullptr,
	                                                                                &graphics_pipeline_)
		!= vk::Result::eSuccess)
	{
		throw std::runtime_error("StandardVulkanGraphicsPipeline: Failed to create graphics pipeline!");
	}
}
