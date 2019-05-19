#pragma once

#include <Engine/Utility/UsefulTypes.h>
#include <Engine/Rendering/Manager/RenderManager.h>
#include <Engine/Rendering/Manager/RenderManagerView.h>
#include <Engine/LogicCore/Manager/LogicManager.h>
#include <Engine/LogicCore/Manager/LogicManagerView.h>

namespace ScrapEngine
{
	namespace Manager
	{
		class EngineManager
		{
		private:
			bool cleanup_done_ = false;

			ScrapEngine::game_base_info received_base_game_info_;

			ScrapEngine::Render::RenderManager* scrap_render_manager_ = nullptr;
			ScrapEngine::Core::LogicManager* scrap_logic_manager_ = nullptr;
		public:
			EngineManager(std::string app_name = "ScrapEngine Game", int app_version = 1, uint32_t window_width = 800,
			              uint32_t window_height = 600, bool fullscreen = false, bool vsync = true);
			~EngineManager();

			void start_game_loop();

			ScrapEngine::Core::LogicManagerView* logic_manager_view;
			ScrapEngine::Render::RenderManagerView* render_manager_view;
		private:
			void initialize_engine();

			void initialize_render_manager(const ScrapEngine::game_base_info* game_info);
			void initialize_logic_manager();
			void initialize_views();

			void main_game_loop() const;

			void cleanup_engine();
		};
	}
}
