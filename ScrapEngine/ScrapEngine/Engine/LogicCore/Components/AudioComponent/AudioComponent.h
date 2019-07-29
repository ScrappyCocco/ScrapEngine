#pragma once

#include <Engine/LogicCore/Components/SComponent.h>
#include <Engine/Audio/Source/AudioSource.h>

namespace ScrapEngine
{
	namespace Core
	{
		class AudioComponent : public SComponent
		{
		protected:
			Audio::AudioSource* audio_source_ = nullptr;
		public:
			AudioComponent(Audio::AudioSource* input_audio_source);
			virtual ~AudioComponent() = 0;

			void set_source_pitch(float pitch) const;
			void set_source_gain(float gain) const;
			void set_source_loop(bool loop) const;

			bool is_playing() const;

			void play() const;
			void stop() const;
			void pause() const;
			void rewind() const;

			//This is used mostly for engine operations
			//And should not be used
			Audio::AudioSource* get_raw_source() const;
		};
	}
}
