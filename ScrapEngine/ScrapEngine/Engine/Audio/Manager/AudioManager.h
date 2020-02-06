#pragma once

#include <string>
#include <unordered_map>

namespace ScrapEngine
{
	namespace Render
	{
		class Camera;
	}
}

namespace ScrapEngine
{
	namespace Audio
	{
		class AudioContext;
		class AudioDevice;
		class AudioBuffer;
		class AudioSource;

		class AudioManager
		{
		private:
			AudioDevice* device_;
			AudioContext* context_;

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
