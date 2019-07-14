#include <Engine/Audio/Manager/AudioManager.h>
#include <Engine/Audio/Buffer/Wav/WavAudioBuffer.h>

ScrapEngine::Audio::AudioBuffer* ScrapEngine::Audio::AudioManager::build_buffer(const std::string& filename)
{
	const std::string extension = filename.substr(filename.length() - 3);

	if (extension == "wav")
	{
		AudioBuffer* buffer = new WavAudioBuffer();
		buffer->load_file(filename);
		return buffer;
	}

	/*if(extension == "mp3")
	{
		Other files can be added in the future
	}*/

	throw std::runtime_error("[AudioManager]This audio extension is not supported: " + extension);
}

ScrapEngine::Audio::AudioManager::AudioManager()
{
	device_ = new AudioDevice();

	context_ = new AudioContext(device_->get_audio_device());
}

ScrapEngine::Audio::AudioManager::~AudioManager()
{
	for (auto& loaded_sound : loaded_audio_)
	{
		delete loaded_sound.second;
		delete loaded_sound.first;
	}
	delete context_;
	delete device_;
}

ScrapEngine::Audio::AudioSource* ScrapEngine::Audio::AudioManager::load_2d_sound(const std::string& filename)
{
	//Create and check buffer
	AudioBuffer* buffer = build_buffer(filename);
	if (!buffer->get_is_stereo())
	{
		throw std::runtime_error("[AudioManager]A 2d sounds must NOT be mono (single channel)!");
	}

	//Load source
	AudioSource* source = new AudioSource(buffer->get_buffer());

	//Register loaded sound
	std::pair<AudioBuffer*, AudioSource*> pair_to_add;
	pair_to_add.first = buffer;
	pair_to_add.second = source;
	loaded_audio_.push_back(pair_to_add);

	return source;
}

ScrapEngine::Audio::AudioSource* ScrapEngine::Audio::AudioManager::load_3d_sound(const std::string& filename)
{
	//Create and check buffer
	AudioBuffer* buffer = build_buffer(filename);
	if (buffer->get_is_stereo())
	{
		throw std::runtime_error("[AudioManager]A 3d sounds must BE mono (single channel) to be 3D-spatialized!");
	}

	//Load source
	AudioSource* source = new AudioSource(buffer->get_buffer());

	//Register loaded sound
	std::pair<AudioBuffer*, AudioSource*> pair_to_add;
	pair_to_add.first = buffer;
	pair_to_add.second = source;
	loaded_audio_.push_back(pair_to_add);

	return source;
}

void ScrapEngine::Audio::AudioManager::unload_sound(AudioSource* sound)
{
	std::pair<AudioBuffer*, AudioSource*> element_to_remove;
	for (auto& loaded_sound : loaded_audio_)
	{
		if (loaded_sound.second == sound)
		{
			element_to_remove = loaded_sound;
			break;
		}
	}
	loaded_audio_.erase(std::remove(loaded_audio_.begin(), loaded_audio_.end(), element_to_remove),
	                    loaded_audio_.end());
	//Delete pointers
	delete element_to_remove.second;
	delete element_to_remove.first;
}

void ScrapEngine::Audio::AudioManager::audio_update(const Render::Camera* camera_ref) const
{
	listener_.set_listener_location(camera_ref->get_camera_location());
	listener_.set_listener_orientation(camera_ref->get_camera_front(), camera_ref->get_camera_up());
}
