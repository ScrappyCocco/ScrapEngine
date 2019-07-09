#include <Engine/Audio/Buffer/AudioBuffer.h>

ALenum ScrapEngine::Audio::AudioBuffer::to_al_format(const short channels, const short samples)
{
	const bool stereo = (channels > 1);

	switch (samples)
	{
	case 16:
		if (stereo)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
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

void ScrapEngine::Audio::AudioBuffer::load_wav_file(const std::string& filename)
{
	//Load the audio file
	audio_file_.load(filename);

	//Set the format
	const ALenum format = to_al_format(audio_file_.getNumChannels(), audio_file_.getBitDepth());

	//Set the sample rate
	const ALsizei freq = static_cast<ALsizei>(audio_file_.getSampleRate());

	//Set the buffer size
	const ALsizei size = static_cast<ALsizei>(sizeof(audio_file_.samples));

	//Fill the buffer
	ALvoid* data = audio_file_.samples.data();

	alBufferData(buffer_, format, data, size, freq);
}

ALuint* ScrapEngine::Audio::AudioBuffer::get_buffer()
{
	return &buffer_;
}
