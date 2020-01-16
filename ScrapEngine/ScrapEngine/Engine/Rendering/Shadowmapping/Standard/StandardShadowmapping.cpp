#include <Engine/Rendering/Shadowmapping/Standard/StandardShadowmapping.h>
#include <Engine/Debug/DebugLog.h>

ScrapEngine::Render::StandardShadowmapping::StandardShadowmapping()
{
	Debug::DebugLog::print_to_console_log("Creating StandardShadowmapping()...");
	offscreen_render_pass_ = new ShadowmappingRenderPass(depth_format_);
	offscreen_frame_buffer_ = new ShadowmappingFrameBuffer(SHADOWMAP_DIM, SHADOWMAP_DIM,
	                                                       depth_format_, shadowmap_filter_, offscreen_render_pass_);
}

ScrapEngine::Render::StandardShadowmapping::~StandardShadowmapping()
{
	delete offscreen_render_pass_;
	delete offscreen_frame_buffer_;
}
