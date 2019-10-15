#pragma once

#include <Engine/LogicCore/Components/SComponent.h>
#include <Engine/Rendering/Model/MeshInstance/VulkanMeshInstance.h>

namespace ScrapEngine
{
	namespace Core
	{
		class CameraComponent : public SComponent
		{
		private:
			Render::Camera* game_camera_ref_ = nullptr;

			void set_rotation(const SVector3& rotation) const;
		public:
			explicit CameraComponent(ScrapEngine::Render::Camera* game_camera);
			~CameraComponent() = default;

			void set_component_location(const SVector3& location) override;
			//Pitch as x, yaw as y, roll as z
			void set_component_rotation(const SVector3& rotation) override;
			void add_component_rotation(const SVector3& rotation) override;

			void set_fov(float fov) const;
			float get_fov() const;

			void set_min_render_distance(float new_render_distance) const;
			void set_max_render_distance(float new_render_distance) const;
			float get_camera_min_draw_distance() const;
			float get_camera_max_draw_distance() const;

			SVector3 get_camera_front() const;
			SVector3 get_camera_up() const;

			virtual void process_mouse_movement(float xpos, float ypos, bool constrain_pitch = true);
			void set_mouse_sensivity(float new_sensivity) const;
			float get_mouse_sensivity() const;

			//Call the standard implementation, then update camera values
			void update_component_location() override;
			void update_component_rotation() override;

			//low-level matrix that might be useful to the user
			glm::mat4 get_camera_projection_matrix() const;
			glm::mat4 get_camera_look_matrix() const;
		};
	}
}
