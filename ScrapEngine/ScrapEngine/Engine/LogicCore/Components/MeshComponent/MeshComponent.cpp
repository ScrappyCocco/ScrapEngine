#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>

ScrapEngine::Core::MeshComponent::MeshComponent(Render::VulkanMeshInstance* input_vulkan_mesh) : SComponent("MeshComponent"),
                                                                                         vulkan_mesh_(input_vulkan_mesh)
{
}

void ScrapEngine::Core::MeshComponent::set_component_location(const glm::vec3& location)
{
	vulkan_mesh_->set_mesh_location(location);
}

void ScrapEngine::Core::MeshComponent::set_component_rotation(const glm::vec3& rotation)
{
	vulkan_mesh_->set_mesh_rotation(rotation);
}

void ScrapEngine::Core::MeshComponent::set_component_scale(const glm::vec3& scale)
{
	vulkan_mesh_->set_mesh_scale(scale);
}

glm::vec3 ScrapEngine::Core::MeshComponent::get_component_location() const
{
	return vulkan_mesh_->get_mesh_location();
}

glm::vec3 ScrapEngine::Core::MeshComponent::get_component_rotation() const
{
	return vulkan_mesh_->get_mesh_rotation();
}

glm::vec3 ScrapEngine::Core::MeshComponent::get_component_scale() const
{
	return vulkan_mesh_->get_mesh_scale();
}
