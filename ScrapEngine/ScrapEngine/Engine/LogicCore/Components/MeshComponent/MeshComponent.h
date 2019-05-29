#pragma once

#include <Engine/LogicCore/Components/SComponent.h>
#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>

namespace ScrapEngine
{
	namespace Core
	{
		class MeshComponent : public SComponent
		{
		private:
			Render::VulkanMeshInstance* vulkan_mesh_;
		public:
			explicit MeshComponent(Render::VulkanMeshInstance* input_vulkan_mesh);
			~MeshComponent() = default;

			void set_component_location(const SVector3& location) override;
			void set_component_rotation(const SVector3& rotation) override;
			void set_component_scale(const SVector3& scale) override;

			//Call the standard implementation, then update vulkan_mesh_ values
			void update_component_location() override;
			void update_component_rotation() override;
			void update_component_scale() override;
		};
	}
}
