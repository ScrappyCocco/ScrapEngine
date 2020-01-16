#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <glm/vec3.hpp>
#include <Engine/Rendering/RenderPass/ShadowmappingRenderPass/ShadowmappingRenderPass.h>

// 16 bits of depth is enough for such a small scene
#define SHADOWMAP_DIM 2048
#define SHADOWMAP_FILTER VK_FILTER_LINEAR

// Offscreen frame buffer properties
#define FB_COLOR_FORMAT VK_FORMAT_R8G8B8A8_UNORM

namespace ScrapEngine
{
	namespace Render
	{
		class StandardShadowmapping
		{
		private:
			ShadowmappingRenderPass* offscreen_render_pass_ = nullptr;
		public:
			StandardShadowmapping();
			~StandardShadowmapping();
		private:
			// 16 bits of depth is enough for such a small scene
			vk::Format depth_format_ = vk::Format::eD16Unorm;
			
			bool filter_pcf_ = true;
			bool display_debug_shadow_map_ = false;

			// Keep depth range as small as possible
			// for better shadow map precision
			float z_near_ = 1.0f;
			float z_far_ = 96.0f;

			// Depth bias (and slope) are used to avoid shadowing artefacts
			// Constant depth bias factor (always applied)
			float depth_bias_constant_ = 1.25f;
			// Slope depth bias factor, applied depending on polygon's slope
			float depth_bias_slope_ = 1.75f;

			glm::vec3 light_pos_ = glm::vec3();
			float light_fov_ = 45.0f;
		};
	}
}

