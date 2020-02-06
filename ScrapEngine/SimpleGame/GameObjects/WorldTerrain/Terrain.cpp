#include "Terrain.h"
#include <Engine/LogicCore/Components/RigidBodyComponent/BoxRigidBodyComponent/BoxRigidBodyComponent.h>
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>
#include <Engine/LogicCore/Components/MeshComponent/MeshComponent.h>
#include <Engine/Physics/RigidBody/RigidBody.h>

Terrain::Terrain(ScrapEngine::Core::ComponentsManager* input_component_manager,
                 const ScrapEngine::Core::SVector3& position,
                 const ScrapEngine::Core::SVector3& scale,
                 const color c)
	: SGameObject("Terrain game object")
{
	set_object_location(position);
	set_object_scale(scale);

	std::string color_texture = "";
	switch (c)
	{
	case color::green:
		color_texture = "../assets/textures/SimpleGreenTexture.png";
		break;
	case color::finish:
		color_texture = "../assets/textures/Finish.png";
		break;
	case color::white:
		color_texture = "../assets/textures/SimpleWhiteTexture.png";
		break;
	}

	//Mesh
	mesh_ = input_component_manager->create_new_mesh_component(
		"../assets/models/terrain_cube.obj",
		{color_texture}
	);
	add_component(mesh_);

	//Collider
	ScrapEngine::Core::RigidBodyComponent* box_collider = input_component_manager->create_box_rigidbody_component(
		scale * 5,
		position, 0.f);

	box_collider->set_rigidbody_type(ScrapEngine::Physics::RigidBody_Types::static_rigidbody);
	add_component(box_collider);
	box_collider->set_friction_coefficient(1);

	//Disable update()
	set_should_update(false);
	mesh_->set_is_static(true);

	//By default disable terrain shadows to save resources
	disable_shadows();
}

void Terrain::disable_shadows() const
{
	mesh_->set_cast_shadows(false);
}

void Terrain::enable_shadows() const
{
	mesh_->set_cast_shadows(true);
}
