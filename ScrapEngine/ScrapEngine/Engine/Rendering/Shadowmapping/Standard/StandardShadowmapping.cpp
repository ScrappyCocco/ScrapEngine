#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>
#include <Engine/Rendering/Base/Vertex.h>

ScrapEngine::Render::StandardShadowmapping::StandardShadowmapping(VulkanSwapChain* swap_chain)
{
	const std::vector<vk::Image>* swap_chain_vector = swap_chain->get_swap_chain_images_vector();
	descriptor_pool_ = new StandardDescriptorPool(swap_chain_vector);

	generate_debug_quad();

	offscreen_render_pass_ = new ShadowmappingRenderPass(depth_format_);
	offscreen_frame_buffer_ = new ShadowmappingFrameBuffer(SHADOWMAP_DIM, SHADOWMAP_DIM,
	                                                       depth_format_, shadowmap_filter_, offscreen_render_pass_);

	debug_quad_descriptor_set_ = new DebugQuadDescriptorSet();
	offscreen_descriptor_set_ = new ShadowmappingDescriptorSet(debug_quad_descriptor_set_->get_descriptor_set_layout());


	quad_ubo_ = new DebugQuadUniformBuffer(swap_chain_vector->size());
	offscreen_ubo_ = new ShadowmappingUniformBuffer(swap_chain_vector->size());

	vk::Extent2D swap_chain_extent = swap_chain->get_swap_chain_extent();
	quad_pipeline_ = new DebugQuadPipeline("../assets/shader/compiled_shaders/quad.vert.spv",
	                                       "../assets/shader/compiled_shaders/quad.vert.spv",
	                                       debug_quad_descriptor_set_->get_pipeline_layout(),
	                                       &swap_chain_extent
	);
	offscreen_pipeline_ = new ShadowmappingPipeline("../assets/shader/compiled_shaders/offscreen.vert.spv",
	                                                offscreen_descriptor_set_->get_pipeline_layout(),
	                                                &swap_chain_extent,
	                                                offscreen_render_pass_
	);

	debug_quad_descriptor_set_->create_descriptor_sets(descriptor_pool_->get_descriptor_pool(),
	                                                   swap_chain->get_swap_chain_images_vector(),
	                                                   quad_ubo_->get_uniform_buffers(),
	                                                   offscreen_frame_buffer_
	                                                   ->get_depth_attachment()->get_image_view(),
	                                                   offscreen_frame_buffer_->get_depth_sampler()
	);
	offscreen_descriptor_set_->create_descriptor_sets(descriptor_pool_->get_descriptor_pool(),
	                                                  swap_chain->get_swap_chain_images_vector(),
	                                                  offscreen_ubo_->get_uniform_buffers()
	);
}

ScrapEngine::Render::StandardShadowmapping::~StandardShadowmapping()
{
	delete quad_vertices_;
	delete quad_indices_;
	delete quad_ubo_;
	delete offscreen_ubo_;
	delete quad_pipeline_;
	delete offscreen_pipeline_;
	delete offscreen_render_pass_;
	delete offscreen_frame_buffer_;
	delete debug_quad_descriptor_set_;
	delete offscreen_descriptor_set_;
	delete descriptor_pool_;
}

void ScrapEngine::Render::StandardShadowmapping::update_uniform_buffers(const uint32_t& current_image,
                                                                        Camera* render_camera) const
{
	offscreen_ubo_->update_uniform_buffer(current_image, light_fov_, light_pos_, z_near_, z_far_);
	quad_ubo_->update_uniform_buffer(current_image, render_camera);
}

glm::vec3 ScrapEngine::Render::StandardShadowmapping::get_light_pos() const
{
	return light_pos_;
}

void ScrapEngine::Render::StandardShadowmapping::set_light_post(const glm::vec3& light_pos_new)
{
	light_pos_ = light_pos_new;
}

glm::mat4 ScrapEngine::Render::StandardShadowmapping::get_depth_bias() const
{
	return offscreen_ubo_->get_depth_bias();
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

ScrapEngine::Render::DebugQuadDescriptorSet* ScrapEngine::Render::StandardShadowmapping::
get_debug_quad_descriptor_set() const
{
	return debug_quad_descriptor_set_;
}

ScrapEngine::Render::ShadowmappingDescriptorSet* ScrapEngine::Render::StandardShadowmapping::
get_offscreen_descriptor_set() const
{
	return offscreen_descriptor_set_;
}

ScrapEngine::Render::DebugQuadPipeline* ScrapEngine::Render::StandardShadowmapping::get_quad_pipeline() const
{
	return quad_pipeline_;
}

ScrapEngine::Render::ShadowmappingPipeline* ScrapEngine::Render::StandardShadowmapping::get_offscreen_pipeline() const
{
	return offscreen_pipeline_;
}

ScrapEngine::Render::VertexBuffer* ScrapEngine::Render::StandardShadowmapping::get_debug_quad_vertices() const
{
	return quad_vertices_;
}

ScrapEngine::Render::IndexBuffer* ScrapEngine::Render::StandardShadowmapping::get_debug_quad_indices() const
{
	return quad_indices_;
}

uint32_t ScrapEngine::Render::StandardShadowmapping::get_quad_index_count() const
{
	return quad_index_count_;
}

vk::Extent2D ScrapEngine::Render::StandardShadowmapping::get_shadow_map_extent()
{
	return vk::Extent2D(SHADOWMAP_DIM, SHADOWMAP_DIM);
}

bool ScrapEngine::Render::StandardShadowmapping::shadowmap_debug_enabled()
{
	return ENABLE_SHADOWMAP_DEBUG;
}

void ScrapEngine::Render::StandardShadowmapping::test_update_light(const float time)
{
	// Animate the light source
	light_pos_.x = cos(glm::radians(time * 360.0f)) * 40.0f;
	light_pos_.y = -50.0f + sin(glm::radians(time * 360.0f)) * 20.0f;
	light_pos_.z = 25.0f + sin(glm::radians(time * 360.0f)) * 5.0f;
}

void ScrapEngine::Render::StandardShadowmapping::generate_debug_quad()
{
	//Vertex buffer

	const glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	const glm::vec3 normal = glm::vec3(0.0f, 0.0f, 1.0f);

	Vertex a;
	a.pos = glm::vec3(1.0f, 1.0f, 0.0f);
	a.color = color;
	a.normal = normal;
	a.tex_coord = glm::vec2(1.0f, 1.0f);

	Vertex b;
	b.pos = glm::vec3(0.0f, 1.0f, 0.0f);
	b.color = color;
	b.normal = normal;
	b.tex_coord = glm::vec2(0.0f, 1.0f);

	Vertex c;
	c.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	c.color = color;
	c.normal = normal;
	c.tex_coord = glm::vec2(0.0f, 0.0f);

	Vertex d;
	d.pos = glm::vec3(1.0f, 0.0f, 0.0f);
	d.color = color;
	d.normal = normal;
	d.tex_coord = glm::vec2(1.0f, 0.0f);

	std::vector<Vertex> vertex_buffer =
	{
		a, b, c, d
	};

	quad_vertices_ = new VertexBuffer(&vertex_buffer);

	//Index buffer

	std::vector<uint32_t> index_buffer = {0, 1, 2, 2, 3, 0};
	quad_indices_ = new IndexBuffer(&index_buffer);

	quad_index_count_ = index_buffer.size();
}
