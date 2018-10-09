#include "MeshComponent.h"

ScrapEngine::MeshComponent::MeshComponent(VulkanMeshInstance* input_VulkanMesh) : SComponent("MeshComponent"), VulkanMesh(input_VulkanMesh)
{

}

void ScrapEngine::MeshComponent::setComponentLocation(glm::vec3 location)
{
	VulkanMesh->setMeshLocation(location);
}

void ScrapEngine::MeshComponent::setComponentRotation(glm::vec3 rotation)
{
	VulkanMesh->setMeshRotation(rotation);
}

void ScrapEngine::MeshComponent::setComponentScale(glm::vec3 scale)
{
	VulkanMesh->setMeshScale(scale);
}

glm::vec3 ScrapEngine::MeshComponent::getComponentLocation()
{
	return VulkanMesh->getMeshLocation();
}

glm::vec3 ScrapEngine::MeshComponent::getComponentRotation()
{
	return VulkanMesh->getMeshRotation();
}

glm::vec3 ScrapEngine::MeshComponent::getComponentScale()
{
	return VulkanMesh->getMeshScale();
}
