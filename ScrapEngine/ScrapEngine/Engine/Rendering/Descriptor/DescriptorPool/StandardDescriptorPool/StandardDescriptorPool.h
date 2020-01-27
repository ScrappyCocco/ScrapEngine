#pragma once

#include <Engine/Rendering/Descriptor/DescriptorPool/BaseDescriptorPool.h>

namespace ScrapEngine
{
	namespace Render
	{
		class StandardDescriptorPool : public BaseDescriptorPool
		{
		public:
			StandardDescriptorPool(size_t size);
			~StandardDescriptorPool() = default;
		};
	}
}
