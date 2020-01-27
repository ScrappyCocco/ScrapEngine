#pragma once

#include <Engine/Rendering/VulkanInclude.h>
#include <glm/vec3.hpp>
#include <Engine/Rendering/RenderPass/ShadowmappingRenderPass/ShadowmappingRenderPass.h>
#include <Engine/Rendering/Buffer/FrameBuffer/ShadowmappingFrameBuffer/ShadowmappingFrameBuffer.h>
#include <Engine/Rendering/Descriptor/DescriptorSet/ShadowmappingDescriptorSet/ShadowmappingDescriptorSet.h>
#include <Engine/Rendering/Buffer/UniformBuffer/ShadowmappingUniformBuffer/ShadowmappingUniformBuffer.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Pipeline/ShadowmappingPipeline/ShadowmappingPipeline.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/StandardDescriptorPool/StandardDescriptorPool.h>

// 16 bits of depth is enough for such a small scene
#define SHADOWMAP_DIM 2048

namespace ScrapEngine
{
	namespace Render
	{
		class StandardShadowmapping
		{
		private:
			ShadowmappingRenderPass* offscreen_render_pass_ = nullptr;
			ShadowmappingFrameBuffer* offscreen_frame_buffer_ = nullptr;

			ShadowmappingDescriptorSet* offscreen_descriptor_set_ = nullptr;

			ShadowmappingPipeline* offscreen_pipeline_ = nullptr;

			StandardDescriptorPool* debug_quad_descriptor_pool_ = nullptr;
			StandardDescriptorPool* offscreen_descriptor_pool_ = nullptr;
		public:
			StandardShadowmapping(VulkanSwapChain* swap_chain);
			~StandardShadowmapping();

			glm::vec3 get_light_pos() const;
			void set_light_pos(const glm::vec3& light_pos_new);

			//glm::mat4 get_depth_bias() const;
			float get_depth_bias_constant() const;
			float get_depth_bias_slope() const;

			ShadowmappingFrameBuffer* get_offscreen_frame_buffer() const;
			ShadowmappingRenderPass* get_offscreen_render_pass() const;
			ShadowmappingPipeline* get_offscreen_pipeline() const;
			static vk::Extent2D get_shadow_map_extent();
			float get_z_near() const;
			float get_z_far() const;
			void set_z_near(float z_near);
			void set_z_far(float z_far);
			float get_light_fov() const;
			static vk::Format get_depth_format();
		private:
			// 16 bits of depth is enough for such a small scene
			static const vk::Format depth_format = vk::Format::eD16Unorm;
			vk::Filter shadowmap_filter_ = vk::Filter::eLinear;

			// Keep depth range as small as possible
			// for better shadow map precision
			float z_near_ = 1.0f;
			float z_far_ = 1024.0f;

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
