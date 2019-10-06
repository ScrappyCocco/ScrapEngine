#include "BaseBuilding.h"

BaseBuilding::BaseBuilding(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
             const ScrapEngine::Core::SVector3& start_pos,
             const ScrapEngine::Core::SVector3& size,
             const color c)
	: SGameObject("Crate game object"), logic_manager_view_(logic_manager_ref),
	  component_manager_ref_(logic_manager_ref->get_components_manager())
{
	std::string color_texture = "../assets/textures/SimpleWhiteTexture.png";
	switch (c)
	{
	case color::white:
		color_texture = "../assets/textures/SimpleWhiteTexture.png";
		break;
	case color::green:
		color_texture = "../assets/textures/SimpleGreenTexture.png";
		break;
	case color::yellow:
		color_texture = "../assets/textures/SimpleYellowTexture.png";
		break;
	case color::grey:
		color_texture = "../assets/textures/SimpleGreyTexture.png";
		break;
	case color::dark_grey:
		color_texture = "../assets/textures/SimpleDarkGreyTexture.png";
		break;
	default:
		color_texture = "../assets/textures/SimpleWhiteTexture.png";
		break;
	}
	
	//Add mesh to that GameObject
	mesh_ = component_manager_ref_->create_new_mesh_component(
		"../assets/shader/compiled_shaders/shader_base.vert.spv",
		"../assets/shader/compiled_shaders/shader_base.frag.spv",
		"../assets/models/cube.obj",
		{ color_texture }
	);
	add_component(mesh_);

	//Disable update()
	set_should_update(false);

	//Set mesh scale
	mesh_->set_component_scale(size);
}

void BaseBuilding::die()
{
	mesh_->set_is_visible(false);
	//Delete mesh
	component_manager_ref_->destroy_mesh_component(mesh_);
	//Delete this
	logic_manager_view_->un_register_game_object(this);
}

BaseBuilding::~BaseBuilding()
{
	//Empty in base class
}
