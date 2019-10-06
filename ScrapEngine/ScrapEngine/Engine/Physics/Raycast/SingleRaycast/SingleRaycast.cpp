#include <Engine/Physics/Raycast/SingleRaycast/SingleRaycast.h>
#include <Engine/Physics/Utils/ConversionUtils.h>

ScrapEngine::Physics::SingleRaycast::SingleRaycast(rp3d::DynamicsWorld* world_ref)
	: world_ref_(world_ref)
{
}

ScrapEngine::Physics::RigidBody* ScrapEngine::Physics::SingleRaycast::search_rigidbody(
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

ScrapEngine::Physics::RaycastResultInfo ScrapEngine::Physics::SingleRaycast::execute_ray(const Core::SVector3& start,
                                                                                         const Core::SVector3& end,
                                                                                         const std::vector<RigidBody*>*
                                                                                         created_rigidbodies)
{
	//Update vector pointer
	created_rigidbodies_ref_ = created_rigidbodies;
	//Clear last result
	last_raycast_result_ = RaycastResultInfo();

	const rp3d::Ray ray(
		ConversionUtils::convert_vector(start),
		ConversionUtils::convert_vector(end));

	world_ref_->raycast(ray, this);

	return last_raycast_result_;
}

reactphysics3d::decimal ScrapEngine::Physics::SingleRaycast::notifyRaycastHit(const reactphysics3d::RaycastInfo& info)
{
	RigidBody* body = search_rigidbody(info.body);

	if (body)
	{
		last_raycast_result_ = RaycastResultInfo(
			ConversionUtils::convert_vector(info.worldPoint),
			ConversionUtils::convert_vector(info.worldNormal),
			static_cast<float>(info.hitFraction),
			body,
			body->get_collision_shape()
		);
	}

	//End the hit on the first object
	return reactphysics3d::decimal(0.0);
}
