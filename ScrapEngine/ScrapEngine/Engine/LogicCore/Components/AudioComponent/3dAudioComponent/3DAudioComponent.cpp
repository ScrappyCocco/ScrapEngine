#include <Engine/LogicCore/Components/AudioComponent/3dAudioComponent/3DAudioComponent.h>

ScrapEngine::Core::AudioComponent3D::AudioComponent3D(Audio::AudioSource* input_audio_source)
	: AudioComponent(input_audio_source)
{
}

void ScrapEngine::Core::AudioComponent3D::set_component_location(const SVector3& location)
{
	SComponent::set_component_location(location);
	audio_source_->set_source_location(get_component_location());
}
