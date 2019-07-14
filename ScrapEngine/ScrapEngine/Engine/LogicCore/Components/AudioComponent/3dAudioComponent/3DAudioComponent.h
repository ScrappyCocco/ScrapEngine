#pragma once

#include <Engine/LogicCore/Components/AudioComponent/AudioComponent.h>

namespace ScrapEngine
{
	namespace Core
	{
		class AudioComponent3D : public AudioComponent
		{
		public:
			AudioComponent3D(Audio::AudioSource* input_audio_source);
			~AudioComponent3D() = default;

			void set_component_location(const SVector3& location) override;
		};
	}
}
