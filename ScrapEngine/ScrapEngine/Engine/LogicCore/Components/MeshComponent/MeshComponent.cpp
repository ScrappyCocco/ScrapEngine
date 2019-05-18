#include "MeshComponent.h"

ScrapEngine::Core::MeshComponent::MeshComponent(Render::VulkanMeshInstance* input_vulkan_mesh) : SComponent("MeshComponent"),
                                                                                         vulkan_mesh_(input_vulkan_mesh)
{
}

void ScrapEngine::Core::MeshComponent::set_component_location(const glm::vec3& location)
{
	vulkan_mesh_->setMeshLocation(location);
}

void ScrapEngine::Core::MeshComponent::set_component_rotation(const glm::vec3& rotation)
{
	vulkan_mesh_->setMeshRotation(rotation);
}

void ScrapEngine::Core::MeshComponent::set_component_scale(const glm::vec3& scale)
{
	vulkan_mesh_->setMeshScale(scale);
}

glm::vec3 ScrapEngine::Core::MeshComponent::get_component_location() const
{
	return vulkan_mesh_->getMeshLocation();
}

glm::vec3 ScrapEngine::Core::MeshComponent::get_component_rotation() const
{
	return vulkan_mesh_->getMeshRotation();
}

glm::vec3 ScrapEngine::Core::MeshComponent::get_component_scale() const
{
	return vulkan_mesh_->getMeshScale();
}
