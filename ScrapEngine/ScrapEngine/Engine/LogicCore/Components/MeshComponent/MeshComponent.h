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

		virtual void setComponentLocation(const glm::vec3& location) override;
		virtual void setComponentRotation(const glm::vec3& rotation) override;
		virtual void setComponentScale(const glm::vec3& scale) override;

		virtual glm::vec3 getComponentLocation() const override;
		virtual glm::vec3 getComponentRotation() const override;
		virtual glm::vec3 getComponentScale() const override;
	};
}
