#include <Engine/Physics/RigidBody/RigidBody.h>

ScrapEngine::Physics::RigidBody::~RigidBody()
{
	delete shape_;
	delete motion_state_;
	delete body_;
}

void ScrapEngine::Physics::RigidBody::set_start_transform(const btTransform& start_transform)
{
	start_transform_ = start_transform;
}

void ScrapEngine::Physics::RigidBody::set_collision_shape(CollisionShape* shape)
{
	shape_ = shape;
}

void ScrapEngine::Physics::RigidBody::set_mass(const float mass)
{
	mass_ = mass;
	is_dynamic_ = mass != 0.f;
}

void ScrapEngine::Physics::RigidBody::set_color(const btVector4& color)
{
	color_ = color;
}

void ScrapEngine::Physics::RigidBody::build_rigidbody(const bool use_motionstate)
{
	if(!shape_)
	{
		return;
	}
	//Calculate local_inertia
	btVector3 local_inertia(0, 0, 0);
	if (is_dynamic_ && shape_)
	{
		shape_->get_collision_shape()->calculateLocalInertia(mass_, local_inertia);
	}
	//Create motion_state_ is necessary
	motion_state_ = nullptr;
	if (use_motionstate)
	{
		motion_state_ = new btDefaultMotionState(start_transform_);
	}
	//Build the btRigidBody
	const btRigidBody::btRigidBodyConstructionInfo c_info(mass_, motion_state_, shape_->get_collision_shape(), local_inertia);
	body_ = new btRigidBody(c_info);
	body_->setUserIndex(-1);
	//Set the transform
	if (!use_motionstate)
	{
		body_->setWorldTransform(start_transform_);
	}
}

btRigidBody* ScrapEngine::Physics::RigidBody::get_rigidbody() const
{
	return body_;
}
