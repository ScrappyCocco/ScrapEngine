#include <Engine/Audio/Buffer/AudioBuffer.h>

ALenum ScrapEngine::Audio::AudioBuffer::to_al_format(const short channels, const short samples)
{
	const bool stereo = (channels > 1);

	switch (samples)
	{
	case 16:
		{
			if (stereo)
			{
				return AL_FORMAT_STEREO16;
			}
			return AL_FORMAT_MONO16;
		}
	case 8:
		{
			if (stereo)
			{
				return AL_FORMAT_STEREO8;
			}
			return AL_FORMAT_MONO8;
		}
	default:
		return -1;
	}
}

ScrapEngine::Audio::AudioBuffer::AudioBuffer()
{
	alGenBuffers(static_cast<ALuint>(1), &buffer_);
}

ScrapEngine::Audio::AudioBuffer::~AudioBuffer()
{
	alDeleteBuffers(1, &buffer_);
}

ALuint* ScrapEngine::Audio::AudioBuffer::get_buffer()
{
	return &buffer_;
}
