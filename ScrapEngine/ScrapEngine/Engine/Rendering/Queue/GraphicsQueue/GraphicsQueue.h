#pragma once

#include <Engine/Rendering/Queue/BaseQueue.h>

namespace ScrapEngine
{
	namespace Render
	{
		class GraphicsQueue : public BaseQueue
		{
		private:
			//Singleton static instance
			static GraphicsQueue* instance_;

			//The constructor is private because this class is a Singleton
			GraphicsQueue() = default;
		public:
			//Method used to init the class with parameters because the constructor is private
			void init(QueueFamilyIndices indices);

			~GraphicsQueue() = default;

			//Singleton static function to get or create a class instance
			static GraphicsQueue* get_instance();
		};
	}
}
