#include <Engine/Audio/Context/AudioContext.h>
#include <stdexcept>

ScrapEngine::Audio::AudioContext::AudioContext(ALCdevice* device)
{
	context_ = alcCreateContext(device, nullptr);
	if (!alcMakeContextCurrent(context_))
	{
		throw std::runtime_error("AudioContext: Failed to make context current");
	}
}

ScrapEngine::Audio::AudioContext::~AudioContext()
{
	alcDestroyContext(context_);
}
