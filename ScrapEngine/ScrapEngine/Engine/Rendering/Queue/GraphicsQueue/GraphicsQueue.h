#pragma once

#include <Engine/Rendering/Queue/BaseQueue.h>

namespace ScrapEngine
{
	namespace Render
	{
		class GraphicsQueue : public BaseQueue
		{
		private:
			static GraphicsQueue* instance_;

			GraphicsQueue() = default;
		public:
			void init(QueueFamilyIndices indices);

			~GraphicsQueue() = default;

			static GraphicsQueue* get_instance();
		};
	}
}
