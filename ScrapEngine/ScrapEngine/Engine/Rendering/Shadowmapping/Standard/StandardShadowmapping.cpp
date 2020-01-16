#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>

ScrapEngine::Render::StandardShadowmapping::StandardShadowmapping()
{
	offscreen_render_pass_ = new ShadowmappingRenderPass();
	offscreen_render_pass_->init(depth_format_);
}

ScrapEngine::Render::StandardShadowmapping::~StandardShadowmapping()
{
	delete offscreen_render_pass_;
}
