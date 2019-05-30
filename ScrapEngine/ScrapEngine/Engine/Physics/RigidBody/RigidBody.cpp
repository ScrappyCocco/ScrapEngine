#include <Engine/Physics/RigidBody/RigidBody.h>

ScrapEngine::Core::STransform ScrapEngine::Physics::RigidBody::convert_transform(const rp3d::Transform& other)
{
	Core::STransform return_tras;

	const rp3d::Vector3& other_pos = other.getPosition();
	return_tras.set_position(Core::SVector3(other_pos.x, other_pos.y, other_pos.z));

	const rp3d::Vector3& other_rot = other.getOrientation().getVectorV();
	return_tras.set_rotation(Core::SVector3(other_rot.x, other_rot.y, other_rot.z));

	return return_tras;
}

ScrapEngine::Physics::RigidBody::~RigidBody()
{
	delete shape_;
}

void ScrapEngine::Physics::RigidBody::set_start_transform(const rp3d::Vector3& init_position,
                                                          const rp3d::Quaternion& init_orientation)
{
	transform_ = rp3d::Transform(init_position, init_orientation);
}

void ScrapEngine::Physics::RigidBody::set_collision_shape(CollisionShape* shape)
{
	if (proxy_shape_)
	{
		body_->removeCollisionShape(proxy_shape_);
	}
	delete shape_;

	shape_ = shape;
	proxy_shape_ = body_->addCollisionShape(shape_->get_collision_shape(),
	                                        rp3d::Transform::identity(), get_mass());
}

void ScrapEngine::Physics::RigidBody::set_mass(const float mass) const
{
	body_->setMass(mass);
}

float ScrapEngine::Physics::RigidBody::get_mass() const
{
	if (body_) {
		return body_->getMass();
	}
	return 0;
}

void ScrapEngine::Physics::RigidBody::set_type(RigidBody_Types type) const
{
	switch(type)
	{
	case static_rigidbody:
		body_->setType(rp3d::BodyType::STATIC);
		break;
	case kinematic_rigidbody:
		body_->setType(rp3d::BodyType::KINEMATIC);
		break;
	default:
	case dynamic_rigidbody:
		body_->setType(rp3d::BodyType::DYNAMIC);
		break;
	}
}

void ScrapEngine::Physics::RigidBody::build_rigidbody(rp3d::DynamicsWorld* dynamic_world)
{
	body_ = dynamic_world->createRigidBody(transform_);
	body_->setMass(1.f);
}

void ScrapEngine::Physics::RigidBody::remove_from_world(rp3d::DynamicsWorld* dynamic_world) const
{
	dynamic_world->destroyRigidBody(body_);
}

rp3d::RigidBody* ScrapEngine::Physics::RigidBody::get_rigidbody() const
{
	return body_;
}

ScrapEngine::Core::STransform ScrapEngine::Physics::RigidBody::get_updated_transform(const float factor)
{
	const rp3d::Transform curr_transform = body_->getTransform();
	const rp3d::Transform interpolated_transform = rp3d::Transform::interpolateTransforms(
		prev_transform_,
		curr_transform,
		factor);
	Core::STransform return_tras = convert_transform(interpolated_transform);

	prev_transform_ = curr_transform;
	return return_tras;
}
