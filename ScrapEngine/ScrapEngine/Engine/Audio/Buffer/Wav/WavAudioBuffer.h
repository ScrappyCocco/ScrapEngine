#pragma once

#include <Engine/Audio/Buffer/AudioBuffer.h>
#include <dr_wav.h>

namespace ScrapEngine
{
	namespace Audio
	{
		class WavAudioBuffer : public AudioBuffer
		{
		private:
			drwav* p_wav_ = nullptr;
		public:
			WavAudioBuffer() = default;
			~WavAudioBuffer();

			void load_file(const std::string& filename) override;
		};
	}
}
