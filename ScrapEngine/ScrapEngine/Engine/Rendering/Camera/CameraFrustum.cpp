#include <Engine/Rendering/Camera/CameraFrustum.h>

void ScrapEngine::Render::CameraFrustum::update(const glm::mat4& matrix)
{
	planes_[LEFT].x = matrix[0].w + matrix[0].x;
	planes_[LEFT].y = matrix[1].w + matrix[1].x;
	planes_[LEFT].z = matrix[2].w + matrix[2].x;
	planes_[LEFT].w = matrix[3].w + matrix[3].x;

	planes_[RIGHT].x = matrix[0].w - matrix[0].x;
	planes_[RIGHT].y = matrix[1].w - matrix[1].x;
	planes_[RIGHT].z = matrix[2].w - matrix[2].x;
	planes_[RIGHT].w = matrix[3].w - matrix[3].x;

	planes_[TOP].x = matrix[0].w - matrix[0].y;
	planes_[TOP].y = matrix[1].w - matrix[1].y;
	planes_[TOP].z = matrix[2].w - matrix[2].y;
	planes_[TOP].w = matrix[3].w - matrix[3].y;

	planes_[BOTTOM].x = matrix[0].w + matrix[0].y;
	planes_[BOTTOM].y = matrix[1].w + matrix[1].y;
	planes_[BOTTOM].z = matrix[2].w + matrix[2].y;
	planes_[BOTTOM].w = matrix[3].w + matrix[3].y;

	planes_[BACK].x = matrix[0].w + matrix[0].z;
	planes_[BACK].y = matrix[1].w + matrix[1].z;
	planes_[BACK].z = matrix[2].w + matrix[2].z;
	planes_[BACK].w = matrix[3].w + matrix[3].z;

	planes_[FRONT].x = matrix[0].w - matrix[0].z;
	planes_[FRONT].y = matrix[1].w - matrix[1].z;
	planes_[FRONT].z = matrix[2].w - matrix[2].z;
	planes_[FRONT].w = matrix[3].w - matrix[3].z;

	for (auto& plane : planes_)
	{
		const float length = sqrtf(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z);
		plane /= length;
	}
}

bool ScrapEngine::Render::CameraFrustum::check_sphere(const glm::vec3& pos, const float radius)
{
	for (auto& plane : planes_)
	{
		if ((plane.x * pos.x) + (plane.y * pos.y) + (plane.z * pos.z) + plane.w <= -radius)
		{
			return false;
		}
	}
	return true;
}
