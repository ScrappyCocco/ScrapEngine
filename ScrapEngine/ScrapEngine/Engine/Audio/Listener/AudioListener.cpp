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

void ScrapEngine::Audio::AudioListener::set_listener_orientation(
	const Core::SVector3& rot1,
	const Core::SVector3& rot2) const
{
	ALfloat pt[6];
	pt[0] = rot1.get_x();
	pt[1] = rot1.get_y();
	pt[2] = rot1.get_z();
	pt[3] = rot2.get_x();
	pt[4] = rot2.get_y();
	pt[5] = rot2.get_z();

	alListenerfv(AL_ORIENTATION, pt);
	assert(alGetError() == AL_NO_ERROR);
}
