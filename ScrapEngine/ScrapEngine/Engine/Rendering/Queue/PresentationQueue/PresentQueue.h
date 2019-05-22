#pragma once

#include <Engine/Rendering/Queue/BaseQueue.h>

namespace ScrapEngine
{
	namespace Render
	{
		class PresentQueue : public BaseQueue
		{
		private:
			//Singleton static instance
			static PresentQueue* instance_;

			//The constructor is private because this class is a Singleton
			PresentQueue() = default;
		public:
			//Method used to init the class with parameters because the constructor is private
			void init(QueueFamilyIndices indices);

			~PresentQueue() = default;

			//Singleton static function to get or create a class instance
			static PresentQueue* get_instance();
		};
	}
}
