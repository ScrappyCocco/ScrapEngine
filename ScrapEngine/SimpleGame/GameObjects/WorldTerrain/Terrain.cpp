#include "Terrain.h"

Terrain::Terrain(ScrapEngine::Core::ComponentsManager* input_component_manager,
                 const ScrapEngine::Core::SVector3& position,
                 const ScrapEngine::Core::SVector3& scale,
                 const color c)
	: SGameObject("Terrain game object")
{
	set_object_location(position);
	set_object_scale(scale);

	std::string color_texture = "../assets/textures/SimpleWhiteTexture.png";
	switch (c)
	{
	case color::green:
		color_texture = "../assets/textures/SimpleGreenTexture.png";
		break;
	case color::red:
		color_texture = "../assets/textures/SimpleRedTexture.png";
		break;
	case color::finish:
		color_texture = "../assets/textures/Finish.png";
		break;
	}

	//Mesh
	ScrapEngine::Core::MeshComponent* mesh = input_component_manager->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{color_texture}
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
	mesh->set_is_static(true);
}
