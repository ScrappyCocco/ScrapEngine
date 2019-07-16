#pragma once

#include <AL/alc.h>

namespace ScrapEngine
{
	namespace Audio
	{
		class AudioContext
		{
		private:
			ALCcontext* context_;
		public:
			AudioContext(ALCdevice* device);

			~AudioContext();
		};
	}
}
