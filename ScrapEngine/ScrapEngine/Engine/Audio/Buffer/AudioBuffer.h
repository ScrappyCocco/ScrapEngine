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
			bool is_stereo_ = false;

			static bool is_stereo(short channels);
			static ALenum to_al_format(short channels, short samples);
		public:
			AudioBuffer();
			virtual ~AudioBuffer();

			virtual void load_file(const std::string& filename) = 0;

			ALuint* get_buffer();
			bool get_is_stereo() const;
		};
	}
}
