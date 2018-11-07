#include "VulkanGraphicsPipeline.h"

#include "../Base/Vertex.h"

ScrapEngine::VulkanGraphicsPipeline::VulkanGraphicsPipeline(const char* vertexShader, const char* fragmentShader, vk::Device* input_deviceRef, vk::Extent2D* swapChainExtent, vk::RenderPass* input_renderPassRef,
	vk::DescriptorSetLayout* descriptorSetLayout, vk::SampleCountFlagBits msaaSamples, bool isSkybox)
	: deviceRef(input_deviceRef)
{
	ShaderManagerRef = new ShaderManager(input_deviceRef);

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
	
	if (deviceRef->createPipelineLayout(&pipelineLayoutInfo, nullptr, &pipelineLayout) != vk::Result::eSuccess) {
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
		*input_renderPassRef,
		0
	);

	if (input_deviceRef->createGraphicsPipelines(nullptr, 1, &pipelineInfo, nullptr, &graphicsPipeline) != vk::Result::eSuccess) {
		throw std::runtime_error("VulkanGraphicsPipeline: Failed to create graphics pipeline!");
	}

	//input_deviceRef->destroyShaderModule(fragShaderModule);
	//input_deviceRef->destroyShaderModule(vertShaderModule);
	//delete ShaderManagerRef;
}


ScrapEngine::VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
{
	deviceRef->destroyPipeline(graphicsPipeline);
	deviceRef->destroyPipelineLayout(pipelineLayout);
}

vk::Pipeline* ScrapEngine::VulkanGraphicsPipeline::getGraphicsPipeline()
{
	return &graphicsPipeline;
}

vk::PipelineLayout* ScrapEngine::VulkanGraphicsPipeline::getPipelineLayout()
{
	return &pipelineLayout;
}
