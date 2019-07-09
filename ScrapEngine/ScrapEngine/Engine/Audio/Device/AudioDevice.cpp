#include <Engine/Audio/Device/AudioDevice.h>
#include <stdexcept>

ScrapEngine::Audio::AudioDevice::AudioDevice()
{
	device_ = alcOpenDevice(nullptr);
	if (!device_)
	{
		throw std::runtime_error("AudioDevice: Failed to open default device");
	}
}

ScrapEngine::Audio::AudioDevice::~AudioDevice()
{
	alcCloseDevice(device_);
}

ALCdevice* ScrapEngine::Audio::AudioDevice::get_audio_device() const
{
	return device_;
}
