#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>
#include <Engine/Rendering/Base/Vertex.h>
#include <Engine/Rendering/RenderPass/ShadowmappingRenderPass/ShadowmappingRenderPass.h>
#include <Engine/Rendering/Buffer/FrameBuffer/ShadowmappingFrameBuffer/ShadowmappingFrameBuffer.h>
#include <Engine/Rendering/Descriptor/DescriptorSet/ShadowmappingDescriptorSet/ShadowmappingDescriptorSet.h>
#include <Engine/Rendering/Buffer/UniformBuffer/ShadowmappingUniformBuffer/ShadowmappingUniformBuffer.h>
#include <Engine/Rendering/SwapChain/VulkanSwapChain.h>
#include <Engine/Rendering/Pipeline/ShadowmappingPipeline/ShadowmappingPipeline.h>
#include <Engine/Rendering/Descriptor/DescriptorPool/StandardDescriptorPool/StandardDescriptorPool.h>
#include <Engine/Rendering/DepthResources/VulkanDepthResources.h>

ScrapEngine::Render::StandardShadowmapping::StandardShadowmapping(VulkanSwapChain* swap_chain)
	: depth_format_(VulkanDepthResources::find_depth_format())
{
	const size_t size = swap_chain->get_swap_chain_images_vector()->size();
	offscreen_descriptor_pool_ = new StandardDescriptorPool(size);

	offscreen_render_pass_ = new ShadowmappingRenderPass(depth_format_);
	offscreen_frame_buffer_ = new ShadowmappingFrameBuffer(shadowmap_dim, shadowmap_dim,
	                                                       depth_format_, shadowmap_filter_, offscreen_render_pass_);

	offscreen_descriptor_set_ = new ShadowmappingDescriptorSet();

	vk::Extent2D shadowmapping_extent(shadowmap_dim, shadowmap_dim);

	offscreen_pipeline_ = new ShadowmappingPipeline("../assets/shader/compiled_shaders/offscreen.vert.spv",
	                                                offscreen_descriptor_set_->get_descriptor_set_layout(),
	                                                &shadowmapping_extent,
	                                                offscreen_render_pass_
	);
}

ScrapEngine::Render::StandardShadowmapping::~StandardShadowmapping()
{
	delete offscreen_render_pass_;
	delete offscreen_frame_buffer_;
	delete offscreen_descriptor_set_;
	delete offscreen_descriptor_pool_;
	delete offscreen_pipeline_;
}

glm::vec3 ScrapEngine::Render::StandardShadowmapping::get_light_pos() const
{
	return light_pos_;
}

void ScrapEngine::Render::StandardShadowmapping::set_light_pos(const glm::vec3& light_pos_new)
{
	light_pos_ = light_pos_new;
}

glm::vec3 ScrapEngine::Render::StandardShadowmapping::get_light_look_at() const
{
	return light_look_at_;
}

void ScrapEngine::Render::StandardShadowmapping::set_light_look_at(const glm::vec3& light_look_new)
{
	light_look_at_ = light_look_new;
}

float ScrapEngine::Render::StandardShadowmapping::get_depth_bias_constant() const
{
	return depth_bias_constant_;
}

float ScrapEngine::Render::StandardShadowmapping::get_depth_bias_slope() const
{
	return depth_bias_slope_;
}

ScrapEngine::Render::ShadowmappingFrameBuffer* ScrapEngine::Render::StandardShadowmapping::
get_offscreen_frame_buffer() const
{
	return offscreen_frame_buffer_;
}

ScrapEngine::Render::ShadowmappingRenderPass* ScrapEngine::Render::StandardShadowmapping::
get_offscreen_render_pass() const
{
	return offscreen_render_pass_;
}

ScrapEngine::Render::ShadowmappingPipeline* ScrapEngine::Render::StandardShadowmapping::get_offscreen_pipeline() const
{
	return offscreen_pipeline_;
}

vk::Extent2D ScrapEngine::Render::StandardShadowmapping::get_shadow_map_extent()
{
	return vk::Extent2D(shadowmap_dim, shadowmap_dim);
}

float ScrapEngine::Render::StandardShadowmapping::get_z_near() const
{
	return z_near_;
}

float ScrapEngine::Render::StandardShadowmapping::get_z_far() const
{
	return z_far_;
}

void ScrapEngine::Render::StandardShadowmapping::set_z_near(const float z_near)
{
	z_near_ = z_near;
}

void ScrapEngine::Render::StandardShadowmapping::set_z_far(const float z_far)
{
	z_far_ = z_far;
}

float ScrapEngine::Render::StandardShadowmapping::get_light_fov() const
{
	return light_fov_;
}

void ScrapEngine::Render::StandardShadowmapping::set_light_fov(const float fov)
{
	light_fov_ = fov;
}

vk::Format ScrapEngine::Render::StandardShadowmapping::get_depth_format()
{
	return VulkanDepthResources::find_depth_format();
}
