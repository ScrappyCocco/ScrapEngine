#pragma once
#include "../SComponent.h"
#include "../../../Rendering/Model/VulkanMeshInstance.h"

namespace ScrapEngine {

	class MeshComponent : public SComponent
	{
	private:
		VulkanMeshInstance* VulkanMesh;
	public:
		MeshComponent(VulkanMeshInstance* input_VulkanMesh);
		~MeshComponent() = default;

		virtual void setComponentLocation(glm::vec3 location);
		virtual void setComponentRotation(glm::vec3 rotation);
		virtual void setComponentScale(glm::vec3 scale);

		virtual glm::vec3 getComponentLocation();
		virtual glm::vec3 getComponentRotation();
		virtual glm::vec3 getComponentScale();
	};

}

