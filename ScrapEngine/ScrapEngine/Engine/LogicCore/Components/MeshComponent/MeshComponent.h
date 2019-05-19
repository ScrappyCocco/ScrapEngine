#pragma once

#include <Engine/LogicCore/Components/SComponent.h>
#include <Engine/Rendering/Model/VulkanMeshInstance.h>

namespace ScrapEngine
{
	namespace Core
	{
		class MeshComponent : public Core::SComponent
		{
		private:
			Render::VulkanMeshInstance* vulkan_mesh_;
		public:
			explicit MeshComponent(Render::VulkanMeshInstance* input_vulkan_mesh);
			~MeshComponent() = default;

			virtual void set_component_location(const glm::vec3& location) override;
			virtual void set_component_rotation(const glm::vec3& rotation) override;
			virtual void set_component_scale(const glm::vec3& scale) override;

			virtual glm::vec3 get_component_location() const override;
			virtual glm::vec3 get_component_rotation() const override;
			virtual glm::vec3 get_component_scale() const override;
		};
	}
}
