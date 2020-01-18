#pragma once

#include <Engine/Rendering/Descriptor/DescriptorSet/BaseDescriptorSet.h>

namespace ScrapEngine
{
	namespace Render
	{
		class GuiDescriptorSet : public BaseDescriptorSet
		{
		public:
			GuiDescriptorSet();
			~GuiDescriptorSet() = default;

			void create_descriptor_sets(vk::DescriptorPool* descriptor_pool,
			                            const std::vector<vk::Image>* swap_chain_images,
			                            vk::Sampler* texture_sampler, vk::ImageView* texture_image_view);
		};
	}
}
