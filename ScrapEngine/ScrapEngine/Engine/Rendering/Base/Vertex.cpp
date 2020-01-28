#include <Engine/Rendering/Base/Vertex.h>

vk::VertexInputBindingDescription ScrapEngine::Render::Vertex::get_binding_description()
{
	return vk::VertexInputBindingDescription(0, sizeof(Vertex), vk::VertexInputRate::eVertex);
}

std::array<vk::VertexInputAttributeDescription, 4> ScrapEngine::Render::Vertex::get_attribute_descriptions()
{
	const std::array<vk::VertexInputAttributeDescription, 4> attribute_descriptions = {
		vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, pos)),
		vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, color)),
		vk::VertexInputAttributeDescription(2, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, tex_coord)),
		vk::VertexInputAttributeDescription(3, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, normal)),
	};

	return attribute_descriptions;
}

vk::VertexInputBindingDescription ScrapEngine::Render::SkyboxVertex::get_binding_description()
{
	return vk::VertexInputBindingDescription(0, sizeof(SkyboxVertex), vk::VertexInputRate::eVertex);
}

std::array<vk::VertexInputAttributeDescription, 3> ScrapEngine::Render::SkyboxVertex::get_attribute_descriptions()
{
	const std::array<vk::VertexInputAttributeDescription, 3> attribute_descriptions = {
		vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32Sfloat, offsetof(SkyboxVertex, pos)),
		vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32Sfloat, offsetof(SkyboxVertex, color)),
		vk::VertexInputAttributeDescription(2, 0, vk::Format::eR32G32Sfloat, offsetof(SkyboxVertex, tex_coord))
	};

	return attribute_descriptions;
}

vk::VertexInputBindingDescription ScrapEngine::Render::OffscreenVertex::get_binding_description()
{
	return vk::VertexInputBindingDescription(0, sizeof(OffscreenVertex), vk::VertexInputRate::eVertex);
}

std::array<vk::VertexInputAttributeDescription, 1> ScrapEngine::Render::OffscreenVertex::get_attribute_descriptions()
{
	const std::array<vk::VertexInputAttributeDescription, 1> attribute_descriptions = {
		vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32Sfloat, offsetof(OffscreenVertex, pos))
	};

	return attribute_descriptions;
}
