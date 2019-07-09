#include <Engine/Audio/Listener/AudioListener.h>
#include <alListener.h>

void ScrapEngine::Audio::AudioListener::set_listener_location(const Core::SVector3& location) const
{
	alListener3f(AL_POSITION, location.get_x(), location.get_y(), location.get_z());
}

void ScrapEngine::Audio::AudioListener::set_listener_velocity(const Core::SVector3& velocity) const
{
	alListener3f(AL_VELOCITY, velocity.get_x(), velocity.get_y(), velocity.get_z());
}
