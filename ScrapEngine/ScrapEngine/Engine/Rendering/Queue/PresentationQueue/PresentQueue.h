#pragma once

#include <Engine/Rendering/Queue/BaseQueue.h>

namespace ScrapEngine
{
	namespace Render
	{
		class PresentQueue : public BaseQueue
		{
		private:
			static PresentQueue* instance_;

			PresentQueue() = default;
		public:
			void init(QueueFamilyIndices indices);

			~PresentQueue() = default;

			static PresentQueue* get_instance();
		};
	}
}
