#include "VulkanGraphicsPipeline.h"

#include "../Base/Vertex.h"
#include "../Base/StaticTypes.h"

ScrapEngine::Render::VulkanGraphicsPipeline::VulkanGraphicsPipeline(const char* vertexShader, const char* fragmentShader, vk::Extent2D* swapChainExtent,
	vk::DescriptorSetLayout* descriptorSetLayout, vk::SampleCountFlagBits msaaSamples, bool isSkybox)
{
	ShaderManagerRef = new ShaderManager();

	auto vertShaderCode = ShaderManager::readFile(vertexShader);
	auto fragShaderCode = ShaderManager::readFile(fragmentShader);

	vk::ShaderModule vertShaderModule = ShaderManagerRef->createShaderModule(vertShaderCode);
	vk::ShaderModule fragShaderModule = ShaderManagerRef->createShaderModule(fragShaderCode);

	vk::PipelineShaderStageCreateInfo vertShaderStageInfo(
		vk::PipelineShaderStageCreateFlags(), 
		vk::ShaderStageFlagBits::eVertex, 
		vertShaderModule, 
		"main"
	);

	vk::PipelineShaderStageCreateInfo fragShaderStageInfo(
		vk::PipelineShaderStageCreateFlags(),
		vk::ShaderStageFlagBits::eFragment,
		fragShaderModule,
		"main"
	);

	vk::PipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	auto attributeDescriptions = Vertex::getAttributeDescriptions();
	auto bindingDescription = Vertex::getBindingDescription();

	vk::PipelineVertexInputStateCreateInfo vertexInputInfo(
		vk::PipelineVertexInputStateCreateFlags(),
		1,
		&bindingDescription,
		static_cast<uint32_t>(attributeDescriptions.size()),
		attributeDescriptions.data()
	);

	vk::PipelineInputAssemblyStateCreateInfo inputAssembly(
		vk::PipelineInputAssemblyStateCreateFlags(), 
		vk::PrimitiveTopology::eTriangleList,
		false
	);

	vk::Viewport viewport(
		0, 
		0, 
		(float)swapChainExtent->width, 
		(float)swapChainExtent->height, 
		0.0f, 
		1.0f);

	vk::Rect2D scissor(
		vk::Offset2D(), 
		*swapChainExtent
	);

	vk::PipelineViewportStateCreateInfo viewportState(
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
		msaaSamples
	);

	vk::PipelineDepthStencilStateCreateInfo depthStencil(
		vk::PipelineDepthStencilStateCreateFlags(),
		true,
		true,
		vk::CompareOp::eLessOrEqual
	);

	vk::PipelineColorBlendAttachmentState colorBlendAttachment;
	colorBlendAttachment.setColorWriteMask(vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);

	vk::PipelineColorBlendStateCreateInfo colorBlending(
		vk::PipelineColorBlendStateCreateFlags(),
		false,
		vk::LogicOp::eCopy,
		1,
		&colorBlendAttachment
	);

	vk::PipelineLayoutCreateInfo pipelineLayoutInfo(
		vk::PipelineLayoutCreateFlags(),
		1,
		&(*descriptorSetLayout)
	);

	if (isSkybox) {
		rasterizer.setCullMode(vk::CullModeFlagBits::eFront);
		depthStencil.setDepthWriteEnable(false);
		depthStencil.setDepthTestEnable(false);
	}
	
	if (VulkanDevice::StaticLogicDeviceRef->createPipelineLayout(&pipelineLayoutInfo, nullptr, &pipelineLayout) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanGraphicsPipeline: Failed to create pipeline layout!");
	}

	vk::GraphicsPipelineCreateInfo pipelineInfo(
		vk::PipelineCreateFlags(),
		2,
		shaderStages,
		&vertexInputInfo,
		&inputAssembly,
		nullptr,
		&viewportState,
		&rasterizer,
		&multisampling,
		&depthStencil,
		&colorBlending,
		nullptr,
		pipelineLayout,
		*VulkanRenderPass::StaticRenderPassRef,
		0
	);

	if (VulkanDevice::StaticLogicDeviceRef->createGraphicsPipelines(nullptr, 1, &pipelineInfo, nullptr, &graphicsPipeline) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanGraphicsPipeline: Failed to create graphics pipeline!");
	}

	VulkanDevice::StaticLogicDeviceRef->destroyShaderModule(fragShaderModule);
	VulkanDevice::StaticLogicDeviceRef->destroyShaderModule(vertShaderModule);
	delete ShaderManagerRef;
}


ScrapEngine::Render::VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
{
	VulkanDevice::StaticLogicDeviceRef->destroyPipeline(graphicsPipeline);
	VulkanDevice::StaticLogicDeviceRef->destroyPipelineLayout(pipelineLayout);
}

vk::Pipeline* ScrapEngine::Render::VulkanGraphicsPipeline::getGraphicsPipeline()
{
	return &graphicsPipeline;
}

vk::PipelineLayout* ScrapEngine::Render::VulkanGraphicsPipeline::getPipelineLayout()
{
	return &pipelineLayout;
}
