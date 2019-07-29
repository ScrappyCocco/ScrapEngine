#include <Engine/LogicCore/Components/AudioComponent/AudioComponent.h>

ScrapEngine::Core::AudioComponent::AudioComponent(Audio::AudioSource* input_audio_source)
	: SComponent("AudioComponent"), audio_source_(input_audio_source)
{
}

ScrapEngine::Core::AudioComponent::~AudioComponent()
{
	delete audio_source_;
}

void ScrapEngine::Core::AudioComponent::set_source_pitch(const float pitch) const
{
	audio_source_->set_source_pitch(pitch);
}

void ScrapEngine::Core::AudioComponent::set_source_gain(const float gain) const
{
	audio_source_->set_source_gain(gain);
}

void ScrapEngine::Core::AudioComponent::set_source_loop(const bool loop) const
{
	audio_source_->set_source_loop(loop);
}

bool ScrapEngine::Core::AudioComponent::is_playing() const
{
	return audio_source_->is_playing();
}

void ScrapEngine::Core::AudioComponent::play() const
{
	audio_source_->play();
}

void ScrapEngine::Core::AudioComponent::stop() const
{
	audio_source_->stop();
}

void ScrapEngine::Core::AudioComponent::pause() const
{
	audio_source_->pause();
}

void ScrapEngine::Core::AudioComponent::rewind() const
{
	audio_source_->rewind();
}

ScrapEngine::Audio::AudioSource* ScrapEngine::Core::AudioComponent::get_raw_source() const
{
	return audio_source_;
}
