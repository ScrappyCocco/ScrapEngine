#include <Engine/Audio/Manager/AudioManager.h>
#include "Engine/Audio/Buffer/AudioBuffer.h"
#include "Engine/Audio/Source/AudioSource.h"

ScrapEngine::Audio::AudioManager::AudioManager()
{
	device_ = new AudioDevice();

	context_ = new AudioContext(device_->get_audio_device());
}

ScrapEngine::Audio::AudioManager::~AudioManager()
{
	delete context_;
	delete device_;
}

void ScrapEngine::Audio::AudioManager::load_wav_sound(const std::string& filename)
{
	AudioBuffer* buffer = new AudioBuffer();
	buffer->load_wav_file(filename);
	AudioSource* source = new AudioSource(buffer->get_buffer());
	listener_.set_listener_location(Core::SVector3(0, 0, 0));
	source->set_source_loop(false);
	source->set_source_gain(10);
	source->set_source_location(Core::SVector3(0, 0, 0));
	source->play();
}
