#pragma once

#include <Engine/LogicCore/Math/Vector/SVector3.h>

namespace ScrapEngine
{
	namespace Audio
	{
		class AudioListener
		{
		public:
			AudioListener() = default;
			~AudioListener() = default;

			void set_listener_location(const Core::SVector3& location) const;
			void set_listener_velocity(const Core::SVector3& velocity) const;
		};
	}
}
