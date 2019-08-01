#pragma once

#include <Engine/Audio/Device/AudioDevice.h>
#include <Engine/Audio/Context/AudioContext.h>
#include <Engine/Audio/Listener/AudioListener.h>
#include <Engine/Rendering/Camera/Camera.h>
#include <Engine/Audio/Source/AudioSource.h>
#include <Engine/Audio/Buffer/AudioBuffer.h>
#include <string>
#include <unordered_map>

namespace ScrapEngine
{
	namespace Audio
	{
		class AudioManager
		{
		private:
			AudioDevice* device_;
			AudioContext* context_;
			AudioListener listener_;

			AudioBuffer* build_buffer(const std::string& filename);

			std::list<std::pair<AudioBuffer*, AudioSource*>> loaded_audio_;
			std::unordered_map<std::string, AudioBuffer*> loaded_buffers_;
		public:
			AudioManager();
			~AudioManager();

			AudioSource* load_2d_sound(const std::string& filename);
			AudioSource* load_3d_sound(const std::string& filename);

			void unload_sound(AudioSource* sound);
			void audio_update(const Render::Camera* camera_ref) const;
		};
	}
}
