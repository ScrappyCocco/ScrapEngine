#include "Coin.h"

Coin::Coin(ScrapEngine::Core::LogicManagerView* logic_manager_ref,
           const ScrapEngine::Core::SVector3& start_pos,
           ScoreManager* score_manager)
	: SGameObject("Coin game object"), logic_manager_view_(logic_manager_ref),
	  component_manager_ref_(logic_manager_ref->get_components_manager()),
	  score_manager_ref_(score_manager)
{
	set_object_location(start_pos);
	//Add mesh to that GameObject
	mesh_ = component_manager_ref_->create_new_mesh_component(
		"../assets/models/coin.obj",
		{"../assets/textures/SimpleYellowTexture.png"}
	);
	add_component(mesh_);

	//Set mesh scale
	mesh_->set_component_scale(ScrapEngine::Core::SVector3(0.7f, 0.7f, 0.7f));

	//Trigger
	box_trigger_ = component_manager_ref_->create_box_trigger_component(
		ScrapEngine::Core::SVector3(8, 8, 8),
		start_pos);
	add_component(box_trigger_);

	//Sound
	coin_sound_ = component_manager_ref_->create_3d_sound("../assets/sounds/coin_sound.wav");
	coin_sound_->set_component_location(start_pos);
	coin_sound_->set_source_gain(100);
}

void Coin::set_collision_test(SGameObject* obj, const int index)
{
	ScrapEngine::Core::RigidBodyComponent* component = nullptr;
	component = dynamic_cast<ScrapEngine::Core::RigidBodyComponent*>((*obj->get_components())[index]);
	if (component)
	{
		test_collision_object_ = component;
	}
}

void Coin::game_update(const float time)
{
	if (sound_started_ && !coin_sound_->is_playing())
	{
		set_should_update(false);
		//Destroy sound
		coin_sound_->stop();
		component_manager_ref_->unload_sound(coin_sound_);
		//Delete trigger
		component_manager_ref_->destroy_trigger_component(box_trigger_);
		//Delete mesh
		//REMEMBER, after this call the pointer is no longer valid and should not be used
		//ALSO if the mesh is connected to a rigidbody, you must delete BOTH togheder to avoid errors
		component_manager_ref_->destroy_mesh_component(mesh_);
		//Delete this
		logic_manager_view_->un_register_game_object(this);
	}
	else
	{
		mesh_->add_component_rotation(ScrapEngine::Core::SVector3(0, 500.f * time, 0));

		if (box_trigger_->test_collision(test_collision_object_))
		{
			if (!coin_sound_->is_playing())
			{
				sound_started_ = true;
				coin_sound_->play();
				//Hide mesh immediatly
				mesh_->set_is_visible(false);
				//Add score
				score_manager_ref_->increase_score();
			}
		}
	}
}
