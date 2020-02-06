#pragma once

#include <Engine/LogicCore/Components/SComponent.h>

namespace ScrapEngine
{
	namespace Render
	{
		class VulkanMeshInstance;
	}
}

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
			void add_component_rotation(const SVector3& rotation) override;

			bool get_is_visible() const;
			void set_is_visible(bool visible) const;

			bool get_is_static() const;
			void set_is_static(bool is_static) const;

			bool get_cast_shadows() const;
			void set_cast_shadows(bool cast_shadows) const;

			//Value to set if the mesh should be hidden when out of view or not
			//Remember that a mesh with this value set to false will be always drawn
			bool get_frustum_check() const;
			void set_frustum_check(bool should_check) const;

			//Call the standard implementation, then update vulkan_mesh_ values
			void update_component_location() override;
			void update_component_rotation() override;
			void update_component_scale() override;
		};
	}
}
