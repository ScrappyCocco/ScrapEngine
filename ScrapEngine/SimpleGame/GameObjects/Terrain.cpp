#include "Terrain.h"
#include <Engine/Debug/DebugLog.h>

Terrain::Terrain(ScrapEngine::Core::ComponentsManager* input_ComponentManager)
	: SGameObject("Test game object"), ComponentManagerRef(input_ComponentManager)
{
	//Add mesh to that GameObject
	set_object_location(ScrapEngine::Core::SVector3(0, -20, 0));
	set_object_scale(ScrapEngine::Core::SVector3(25, 0.5f, 25));

	ScrapEngine::Core::MeshComponent* mesh = input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/SimpleWhiteTexture.png" }
	);
	add_component(mesh);

	ScrapEngine::Core::RigidBodyComponent* box_collider = input_ComponentManager->create_box_rigidbody_component(
		ScrapEngine::Core::SVector3(2500.f, 0.5f, 2500.f),
		ScrapEngine::Core::SVector3(0, -20, 0), 0.f);
	
	box_collider->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	add_component(box_collider);
	box_collider->set_friction_coefficient(1.f);

	//Disable update()
	set_should_update(false);
}
