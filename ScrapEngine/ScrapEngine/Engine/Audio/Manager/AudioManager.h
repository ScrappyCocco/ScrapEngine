#pragma once
#include <Engine/Audio/Device/AudioDevice.h>
#include <Engine/Audio/Context/AudioContext.h>
#include <Engine/Audio/Listener/AudioListener.h>
#include <string>

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
		public:
			AudioManager();
			~AudioManager();

			void load_wav_sound(const std::string& filename);
		};
	}
}
