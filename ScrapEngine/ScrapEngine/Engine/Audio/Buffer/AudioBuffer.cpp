#include <Engine/Audio/Buffer/AudioBuffer.h>

bool ScrapEngine::Audio::AudioBuffer::is_stereo(const short channels)
{
	return channels > 1;
}

ALenum ScrapEngine::Audio::AudioBuffer::to_al_format(const short channels, const short samples)
{
	const bool stereo = is_stereo(channels);

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

bool ScrapEngine::Audio::AudioBuffer::get_is_stereo() const
{
	return is_stereo_;
}
