#include "Crate.h"
#include <Engine/Debug/DebugLog.h>

Crate::Crate(ScrapEngine::Core::ComponentsManager* input_ComponentManager, const ScrapEngine::Core::SVector3& start_pos)
	: SGameObject("Test game object"), ComponentManagerRef(input_ComponentManager)
{
	//Add mesh to that GameObject
	ScrapEngine::Core::MeshComponent* mesh = input_ComponentManager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ "../assets/textures/Simple_Wood_Crate_Color.png" }
	);
	add_component(mesh);

	ScrapEngine::Core::RigidBodyComponent* box_collider = input_ComponentManager->create_box_rigidbody_component(
		ScrapEngine::Core::SVector3(8.f, 8.f, 8.f),
		start_pos, 1.f);
	
	add_component(box_collider);

	box_collider->attach_to_mesh(mesh);
	box_collider->set_bounciness(0.f);
	box_collider->set_friction_coefficient(1);

	//Disable update()
	set_should_update(false);

	//Set mesh scale
	mesh->set_component_scale(ScrapEngine::Core::SVector3(1.5f, 1.5f, 1.5f));
}
