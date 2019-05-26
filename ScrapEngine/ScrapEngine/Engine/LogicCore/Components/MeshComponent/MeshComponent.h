#pragma once

#include <Engine/LogicCore/Components/SComponent.h>
#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>

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

			void set_component_location(const glm::vec3& location) override;
			void set_component_rotation(const glm::vec3& rotation) override;
			void set_component_scale(const glm::vec3& scale) override;

			void update_component_location() override;
		};
	}
}
