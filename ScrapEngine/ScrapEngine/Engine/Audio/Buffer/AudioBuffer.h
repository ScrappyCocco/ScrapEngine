#pragma once

#include <AL/al.h>
#include <string>

namespace ScrapEngine
{
	namespace Audio
	{
		class AudioBuffer
		{
		protected:
			ALuint buffer_;

			static ALenum to_al_format(short channels, short samples);
		public:
			AudioBuffer();
			virtual ~AudioBuffer() = 0;

			virtual void load_file(const std::string& filename) = 0;

			ALuint* get_buffer();
		};
	}
}
