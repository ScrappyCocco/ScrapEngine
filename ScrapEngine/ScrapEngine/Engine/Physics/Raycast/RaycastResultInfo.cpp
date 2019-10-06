#include <Engine/Physics/Raycast/RaycastResultInfo.h>

ScrapEngine::Physics::RaycastResultInfo::RaycastResultInfo(const Core::SVector3& p_world_point,
                                                           const Core::SVector3& p_world_normal,
                                                           const float p_hit_fraction, RigidBody* p_body,
                                                           CollisionShape* p_proxy_shape)
	: world_point(p_world_point), world_normal(p_world_normal), hit_fraction(p_hit_fraction), body(p_body),
	  proxy_shape(p_proxy_shape)
{
}
