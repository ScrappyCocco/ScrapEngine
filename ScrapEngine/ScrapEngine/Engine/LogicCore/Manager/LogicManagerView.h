#pragma once

namespace ScrapEngine
{
	namespace Audio
	{
		class AudioManager;
	}
}

namespace ScrapEngine
{
	namespace Physics
	{
		class PhysicsManager;
	}
}

namespace ScrapEngine
{
	namespace Render
	{
		class RenderManager;
	}
}

namespace ScrapEngine
{
	namespace Core
	{
		class SGameObject;
		class SceneManager;
		class ComponentsManager;
		class LogicManager;

		class LogicManagerView
		{
		private:
			LogicManager* logic_manager_ref_ = nullptr;
			ComponentsManager* component_manager_ = nullptr;
			SceneManager* scene_manager_ = nullptr;
		public:
			LogicManagerView(Render::RenderManager* input_render_manager_ref,
			                 LogicManager* input_logic_manager_ref);
			~LogicManagerView();

			void set_physics_manager(Physics::PhysicsManager* physics_manager) const;
			void set_audio_manager(Audio::AudioManager* audio_manager) const;

			SGameObject* register_game_object(SGameObject* input_game_object) const;
			//WARNING un-registering an object also delete it!
			void un_register_game_object(SGameObject* input_game_object) const;
			void delete_game_object(SGameObject* input_game_object) const;

			ComponentsManager* get_components_manager() const;
			SceneManager* get_scene_manager() const;
		};
	}
}
