#pragma once

#include <Engine/LogicCore/Components/SComponent.h>

namespace ScrapEngine
{
	namespace Physics
	{
		enum class RigidBody_Types;
		class RigidBody;
	}
}

namespace ScrapEngine
{
	namespace Core
	{
		class MeshComponent;

		class RigidBodyComponent : public SComponent
		{
		private:
			Physics::RigidBody* rigidbody_ = nullptr;

			MeshComponent* attached_mesh_ = nullptr;

			//Friend class to let TriggerComponent get "rigidbody_"
			friend class TriggerComponent;

			//Parameters that check if a dynamic rigidbody should update mesh data
			bool update_mesh_position_ = true;
			bool update_mesh_rotation_ = true;
		public:
			RigidBodyComponent(Physics::RigidBody* rigidbody);
			virtual ~RigidBodyComponent();

			//This methods will be used when the rigidbody is static and the user move the object with it
			//They will have no effect with a Rigidbody
			void set_component_location(const SVector3& location) override;
			void set_component_rotation(const SVector3& rotation) override;
			//If the user is really sure to change the position, will use this method
			void modify_rigidbody_location(const SVector3& location) const;

			void attach_to_mesh(MeshComponent* mesh);
			void update_transform(float factor) const;
			void set_rigidbody_type(Physics::RigidBody_Types type) const;

			float get_bounciness() const;
			void set_bounciness(float bounce_factor) const;

			float get_friction_coefficient() const;
			void set_friction_coefficient(float coefficient) const;

			bool get_allowed_to_sleep() const;
			void set_allowed_to_sleep(bool allowed) const;

			void apply_force_to_center(const SVector3& force) const;
			void apply_torqe(const SVector3& force) const;

			void cancel_rigidbody_forces() const;

			//Set if the mesh must be updated with new rigidbody data or not
			void set_update_mesh_position(bool update);
			void set_update_mesh_rotation(bool update);
		};
	}
}
