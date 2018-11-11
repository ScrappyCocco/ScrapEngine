#include "MeshComponent.h"

ScrapEngine::MeshComponent::MeshComponent(VulkanMeshInstance* input_VulkanMesh) : SComponent("MeshComponent"), VulkanMesh(input_VulkanMesh)
{

}

void ScrapEngine::MeshComponent::setComponentLocation(const glm::vec3& location)
{
	VulkanMesh->setMeshLocation(location);
}

void ScrapEngine::MeshComponent::setComponentRotation(const glm::vec3& rotation)
{
	VulkanMesh->setMeshRotation(rotation);
}

void ScrapEngine::MeshComponent::setComponentScale(const glm::vec3& scale)
{
	VulkanMesh->setMeshScale(scale);
}

glm::vec3 ScrapEngine::MeshComponent::getComponentLocation() const
{
	return VulkanMesh->getMeshLocation();
}

glm::vec3 ScrapEngine::MeshComponent::getComponentRotation() const
{
	return VulkanMesh->getMeshRotation();
}

glm::vec3 ScrapEngine::MeshComponent::getComponentScale() const
{
	return VulkanMesh->getMeshScale();
}
