#include "Music.h"
#include <Engine/LogicCore/Components/Manager/ComponentsManager.h>
#include <Engine/LogicCore/Components/AudioComponent/2dAudioComponent/2DAudioComponent.h>

Music::Music(ScrapEngine::Core::ComponentsManager* input_component_manager)
	: SGameObject("Music object")
{
	//Disable update call
	set_should_update(false);

	//Load audio 3D, example code
	//You can see Coin.cpp for this (it has a 3D sound)
	/*audio_ = input_ComponentManager->create_3d_sound("../assets/sounds/mono_test_shot.wav");
	audio_->set_component_location(ScrapEngine::Core::SVector3(0, 0, 0));
	audio_->set_source_gain(100);
	audio_->set_source_loop(true);*/

	//In the example scene i will just add a 2d background loop music
	audio_ = input_component_manager->create_2d_sound("../assets/sounds/ambient_music_loop.wav");
	audio_->set_source_gain(0.25f);
	audio_->set_source_loop(true);
}

void Music::game_start()
{
	audio_->play();
}
