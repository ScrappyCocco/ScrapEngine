#include <Engine/Physics/CollisionBody/CollisionBody.h>


ScrapEngine::Physics::CollisionBody::~CollisionBody()
{
	delete shape_;
}

void ScrapEngine::Physics::CollisionBody::set_start_transform(const rp3d::Vector3& init_position,
                                                              const rp3d::Quaternion& init_orientation)
{
	transform_ = rp3d::Transform(init_position, init_orientation);
}

void ScrapEngine::Physics::CollisionBody::set_collision_shape(CollisionShape* shape)
{
	if (proxy_shape_)
	{
		body_->removeCollisionShape(proxy_shape_);
	}
	delete shape_;

	shape_ = shape;
	proxy_shape_ = body_->addCollisionShape(shape_->get_collision_shape(),
	                                        rp3d::Transform::identity());
}

void ScrapEngine::Physics::CollisionBody::build_collision_body(rp3d::DynamicsWorld* dynamic_world)
{
	body_ = dynamic_world->createCollisionBody(transform_);
}

void ScrapEngine::Physics::CollisionBody::remove_from_world(rp3d::DynamicsWorld* dynamic_world) const
{
	dynamic_world->destroyCollisionBody(body_);
}

rp3d::CollisionBody* ScrapEngine::Physics::CollisionBody::get_collision_body() const
{
	return body_;
}

void ScrapEngine::Physics::CollisionBody::update_trasform(const Core::STransform& trasform) const
{
	const Core::SVector3 pos = trasform.get_position();
	const Core::SVector3 rot = trasform.get_rotation();
	const rp3d::Vector3 position(pos.get_x(), pos.get_y(), pos.get_z());
	const rp3d::Vector3 rotation_v(rot.get_x(), rot.get_y(), rot.get_z());
	const rp3d::Quaternion rotation(rotation_v, 0);

	const rp3d::Transform new_transform(position, rotation);
	body_->setTransform(new_transform);
}
