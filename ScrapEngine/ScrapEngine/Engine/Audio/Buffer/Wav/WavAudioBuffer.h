#pragma once

#include <Engine/Audio/Buffer/AudioBuffer.h>

namespace ScrapEngine
{
	namespace Audio
	{
		class WavAudioBuffer : public AudioBuffer
		{
		public:
			WavAudioBuffer() = default;
			~WavAudioBuffer() = default;

			void load_file(const std::string& filename) override;
		};
	}
}
