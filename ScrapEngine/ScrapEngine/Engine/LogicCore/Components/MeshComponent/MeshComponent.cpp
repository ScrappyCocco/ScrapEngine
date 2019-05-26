#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>

ScrapEngine::Core::MeshComponent::MeshComponent(Render::VulkanMeshInstance* input_vulkan_mesh)
	: SComponent("MeshComponent"), vulkan_mesh_(input_vulkan_mesh)
{
}

void ScrapEngine::Core::MeshComponent::set_component_location(const glm::vec3& location)
{
	SComponent::set_component_location(location);
	vulkan_mesh_->set_mesh_location(location);
}

void ScrapEngine::Core::MeshComponent::set_component_rotation(const glm::vec3& rotation)
{
	SComponent::set_component_rotation(rotation);
	vulkan_mesh_->set_mesh_rotation(rotation);
}

void ScrapEngine::Core::MeshComponent::set_component_scale(const glm::vec3& scale)
{
	SComponent::set_component_scale(scale);
	vulkan_mesh_->set_mesh_scale(scale);
}

void ScrapEngine::Core::MeshComponent::update_component_location()
{
	SComponent::update_component_location();
	vulkan_mesh_->set_mesh_location(get_component_location());
}
