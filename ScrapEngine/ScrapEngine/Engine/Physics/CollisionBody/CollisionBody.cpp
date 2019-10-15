#include <Engine/Physics/CollisionBody/CollisionBody.h>
#include <Engine/Physics/Utils/ConversionUtils.h>


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
	world_ref_ = dynamic_world;
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
	body_->setTransform(ConversionUtils::convert_transform(trasform));
}

bool ScrapEngine::Physics::CollisionBody::test_collision(rp3d::CollisionBody* other_body) const
{
	return world_ref_->testOverlap(body_, other_body);
}

bool ScrapEngine::Physics::CollisionBody::test_collision(CollisionBody* other_body) const
{
	return test_collision(other_body->body_);
}
