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
			//More documentation about the mesh is inside the render mesh class
			//If you need anything try to check Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h
			Render::VulkanMeshInstance* vulkan_mesh_;
		public:
			explicit MeshComponent(Render::VulkanMeshInstance* input_vulkan_mesh);
			~MeshComponent() = default;

			void set_component_location(const SVector3& location) override;
			void set_component_rotation(const SVector3& rotation) override;
			void set_component_scale(const SVector3& scale) override;
			void add_component_rotation(const SVector3& rotation) override;

			//Get/Set if the mesh is visible in game
			bool get_is_visible() const;
			void set_is_visible(bool visible) const;

			//Get/Set if the mesh is static in game
			//Remember you can't move a static object
			bool get_is_static() const;
			void set_is_static(bool is_static) const;

			//Get/Set if the mesh project its shadows on the world
			//Remember the mesh will still be affected by sun
			//If you want an object not affected by sun lights,
			//you can load shader_base_NO_shadow.frag.spv as fragment shader
			bool get_cast_shadows() const;
			void set_cast_shadows(bool cast_shadows) const;

			//Value to set if the mesh should be hidden when out of view or not
			//Remember that a mesh with this value set to false will be always drawn
			bool get_frustum_check() const;
			void set_frustum_check(bool should_check) const;

			//Radius to check if the object is in the camera-view frustum or not
			//Also known as "Occlusion culling"
			//If you need, you can reduce/increase this value for specific objects
			float get_frustum_check_radius() const;
			void set_frustum_check_radius(float radius) const;

			//Call the standard implementation, then update vulkan_mesh_ values
			void update_component_location() override;
			void update_component_rotation() override;
			void update_component_scale() override;
		};
	}
}
