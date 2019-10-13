#include <Engine/Physics/Raycast/MultiRaycast/MultiRaycast.h>
#include <Engine/Physics/Utils/ConversionUtils.h>

ScrapEngine::Physics::MultiRaycast::MultiRaycast(rp3d::DynamicsWorld* world_ref)
	: world_ref_(world_ref)
{
}

std::vector<ScrapEngine::Physics::RaycastResultInfo> ScrapEngine::Physics::MultiRaycast::execute_ray(
	const Core::SVector3& start, const Core::SVector3& end, const std::vector<RigidBody*>* created_rigidbodies)
{
	//Update vector pointer
	created_rigidbodies_ref_ = created_rigidbodies;
	//Clear last result
	last_raycast_result_.clear();

	const rp3d::Ray ray(
		ConversionUtils::convert_vector(start),
		ConversionUtils::convert_vector(end));

	world_ref_->raycast(ray, this);

	return last_raycast_result_;
}

ScrapEngine::Physics::RigidBody* ScrapEngine::Physics::MultiRaycast::search_rigidbody(
	const rp3d::CollisionBody* body) const
{
	if (!body)
	{
		return nullptr;
	}

	const std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<RigidBody*>>> search_iterator =
		std::find_if(
			created_rigidbodies_ref_->begin(),
			created_rigidbodies_ref_->end(),
			[body](RigidBody* obj) { return obj->get_rigidbody() == body; }
		);

	if (search_iterator != created_rigidbodies_ref_->end())
	{
		return *search_iterator;
	}

	return nullptr;
}

reactphysics3d::decimal ScrapEngine::Physics::MultiRaycast::notifyRaycastHit(const reactphysics3d::RaycastInfo& info)
{
	RigidBody* body = search_rigidbody(info.body);

	if (body)
	{
		last_raycast_result_.emplace_back(
			ConversionUtils::convert_vector(info.worldPoint),
			ConversionUtils::convert_vector(info.worldNormal),
			static_cast<float>(info.hitFraction),
			body,
			body->get_collision_shape()
		);
	}

	//End the hit on the first object
	return reactphysics3d::decimal(1.0);
}
