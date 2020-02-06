#pragma once

namespace ScrapEngine
{
	namespace Core
	{
		class SVector3;
	}
}

namespace ScrapEngine
{
	namespace Audio
	{
		class AudioListener
		{
		public:
			AudioListener() = default;
			~AudioListener() = default;

			static void set_listener_location(const Core::SVector3& location);
			static void set_listener_velocity(const Core::SVector3& velocity);
			static void set_listener_orientation(const Core::SVector3& rot1, const Core::SVector3& rot2);
		};
	}
}
