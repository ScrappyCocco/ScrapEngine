#pragma once

#include <AL/al.h>
#include <string>
#include <AudioFile.h>

namespace ScrapEngine
{
	namespace Audio
	{
		class AudioBuffer
		{
		private:
			AudioFile<double> audio_file_;
			AudioFile<double>::AudioBuffer audio_buffer_;
			ALuint buffer_;

			ALenum to_al_format(short channels, short samples);
		public:
			AudioBuffer();
			~AudioBuffer();

			void load_wav_file(const std::string& filename);

			ALuint* get_buffer();
		};
	}
}
