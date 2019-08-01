#pragma once

#include <AL/al.h>
#include <Engine/LogicCore/Math/Vector/SVector3.h>

namespace ScrapEngine
{
	namespace Audio
	{
		class AudioSource
		{
		private:
			ALuint source_;
		public:
			AudioSource(const ALuint* audio_buffer);
			~AudioSource();

			void set_source_location(const Core::SVector3& location) const;
			void set_source_velocity(const Core::SVector3& velocity) const;
			void set_source_pitch(float pitch) const;
			void set_source_gain(float gain) const;
			void set_source_loop(bool loop) const;

			bool is_playing() const;

			void play() const;
			void stop() const;
			void pause() const;
			void rewind() const;
		};
	}
}
