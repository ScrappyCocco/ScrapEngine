#include <Engine/LogicCore/Math/Quaternion/SQuaternion.h>

ScrapEngine::Core::SQuaternion::SQuaternion(const glm::quat input)
{
	quat_ = glm::quat(input);
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SQuaternion::rotate_vector(const SVector3& other) const
{
	const SVector3 q(quat_.x, quat_.y, quat_.z);
	const SVector3 t = SVector3::cross_product(q, other) * 2.f;
	const SVector3 result = other + (t * quat_.w) + SVector3::cross_product(q, t);
	return result;
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SQuaternion::unrotate_vector(const SVector3& other) const
{
	const SVector3 q(-quat_.x, -quat_.y, -quat_.z); // Inverse
	const SVector3 t = SVector3::cross_product(q, other) * 2.f;
	const SVector3 result = other + (t * quat_.w) + SVector3::cross_product(q, t);
	return result;
}

ScrapEngine::Core::SQuaternion::SQuaternion()
{
	quat_ = glm::quat();
}

ScrapEngine::Core::SQuaternion::SQuaternion(const float x, const float y, const float z, const float w)
{
	quat_ = glm::quat(x, y, z, w);
}

ScrapEngine::Core::SQuaternion::SQuaternion(const SVector3& euler_angles)
{
	quat_ = glm::quat(glm::vec3(euler_angles.get_x(), euler_angles.get_y(), euler_angles.get_z()));
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SQuaternion::get_axis_x() const
{
	return rotate_vector(SVector3(1.f, 0.f, 0.f));
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SQuaternion::get_axis_y() const
{
	return rotate_vector(SVector3(0.f, 1.f, 0.f));
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SQuaternion::get_axis_z() const
{
	return rotate_vector(SVector3(0.f, 0.f, 1.f));
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SQuaternion::get_forward_vector() const
{
	return get_axis_x();
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SQuaternion::get_right_vector() const
{
	return get_axis_y();
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::SQuaternion::get_up_vector() const
{
	return get_axis_z();
}

glm::quat ScrapEngine::Core::SQuaternion::get_glm_quat() const
{
	return quat_;
}
