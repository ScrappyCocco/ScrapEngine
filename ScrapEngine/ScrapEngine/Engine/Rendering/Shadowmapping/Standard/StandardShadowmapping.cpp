#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>
#include <Engine/Rendering/Base/Vertex.h>

ScrapEngine::Render::StandardShadowmapping::StandardShadowmapping(VulkanSwapChain* swap_chain)
{
	const size_t size = swap_chain->get_swap_chain_images_vector()->size();
	debug_quad_descriptor_pool_ = new StandardDescriptorPool(size);
	offscreen_descriptor_pool_ = new StandardDescriptorPool(size);

	offscreen_render_pass_ = new ShadowmappingRenderPass(depth_format_);
	offscreen_frame_buffer_ = new ShadowmappingFrameBuffer(SHADOWMAP_DIM, SHADOWMAP_DIM,
	                                                       depth_format_, shadowmap_filter_, offscreen_render_pass_);

	offscreen_descriptor_set_ = new ShadowmappingDescriptorSet();

	vk::Extent2D swap_chain_extent = swap_chain->get_swap_chain_extent();

	offscreen_pipeline_ = new ShadowmappingPipeline("../assets/shader/compiled_shaders/offscreen.vert.spv",
	                                                offscreen_descriptor_set_->get_descriptor_set_layout(),
	                                                &swap_chain_extent,
	                                                offscreen_render_pass_
	);
}

ScrapEngine::Render::StandardShadowmapping::~StandardShadowmapping()
{
	delete offscreen_render_pass_;
	delete offscreen_frame_buffer_;
	delete offscreen_descriptor_set_;
	delete debug_quad_descriptor_pool_;
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

/*glm::mat4 ScrapEngine::Render::StandardShadowmapping::get_depth_bias() const
{
	return offscreen_ubo_->get_depth_bias();
}*/

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
	return vk::Extent2D(SHADOWMAP_DIM, SHADOWMAP_DIM);
}

float ScrapEngine::Render::StandardShadowmapping::get_z_near() const
{
	return z_near_;
}

float ScrapEngine::Render::StandardShadowmapping::get_z_far() const
{
	return z_far_;
}

float ScrapEngine::Render::StandardShadowmapping::get_light_fov() const
{
	return light_fov_;
}
