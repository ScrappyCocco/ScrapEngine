#pragma once

#include <Engine/Rendering/Descriptor/DescriptorPool/BaseDescriptorPool.h>

namespace ScrapEngine
{
	namespace Render
	{
		class GuiDescriptorPool : public BaseDescriptorPool
		{
		public:
			GuiDescriptorPool(size_t size);
		};
	}
}
