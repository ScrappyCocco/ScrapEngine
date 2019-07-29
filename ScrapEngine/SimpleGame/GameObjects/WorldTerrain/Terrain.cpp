#include "Terrain.h"
#include <Engine/Debug/DebugLog.h>

Terrain::Terrain(ScrapEngine::Core::ComponentsManager* input_component_manager,
                 const ScrapEngine::Core::SVector3& position,
                 const ScrapEngine::Core::SVector3& scale)
	: SGameObject("Terrain game object")
{
	set_object_location(position);
	set_object_scale(scale);

	//Mesh
	ScrapEngine::Core::MeshComponent* mesh = input_component_manager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{"../assets/textures/SimpleWhiteTexture.png"}
	);
	add_component(mesh);

	//Collider
	ScrapEngine::Core::RigidBodyComponent* box_collider = input_component_manager->create_box_rigidbody_component(
		scale * 5,
		position, 0.f);

	box_collider->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	add_component(box_collider);
	box_collider->set_friction_coefficient(1);

	//Disable update()
	set_should_update(false);
}
