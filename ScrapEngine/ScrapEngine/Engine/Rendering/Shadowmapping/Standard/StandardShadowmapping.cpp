#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>
#include <Engine/Debug/DebugLog.h>
#include <Engine/Rendering/Base/Vertex.h>
#include <Engine/Rendering/Descriptor/DescriptorSet/ShadowmappingDescriptorSet/DebugQuadDescriptorSet.h>
#include <Engine/Rendering/Descriptor/DescriptorSet/ShadowmappingDescriptorSet/ShadowmappingDescriptorSet.h>

ScrapEngine::Render::StandardShadowmapping::StandardShadowmapping(BaseDescriptorSet* scene_descriptor,
                                                                  const size_t swap_chain_images_size)
{
	Debug::DebugLog::print_to_console_log("Creating StandardShadowmapping()...");
	generate_debug_quad();
	offscreen_render_pass_ = new ShadowmappingRenderPass(depth_format_);
	offscreen_frame_buffer_ = new ShadowmappingFrameBuffer(SHADOWMAP_DIM, SHADOWMAP_DIM,
	                                                       depth_format_, shadowmap_filter_, offscreen_render_pass_);

	debug_quad_descriptor_set_ = new DebugQuadDescriptorSet(scene_descriptor->get_descriptor_set_layout());
	offscreen_descriptor_set_ = new ShadowmappingDescriptorSet(scene_descriptor->get_descriptor_set_layout());

	quad_ubo_ = new DebugQuadUniformBuffer(swap_chain_images_size);
	offscreen_ubo_ = new ShadowmappingUniformBuffer(swap_chain_images_size);
}

ScrapEngine::Render::StandardShadowmapping::~StandardShadowmapping()
{
	delete offscreen_render_pass_;
	delete offscreen_frame_buffer_;
	delete quad_vertices_;
	delete quad_indices_;
	delete debug_quad_descriptor_set_;
	delete offscreen_descriptor_set_;
	delete quad_ubo_;
	delete offscreen_ubo_;
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
}
