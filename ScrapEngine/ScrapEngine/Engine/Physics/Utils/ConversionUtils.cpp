#include <Engine/Physics/Utils/ConversionUtils.h>

ScrapEngine::Core::STransform ScrapEngine::Physics::ConversionUtils::convert_transform(const rp3d::Transform& other)
{
	Core::STransform return_tras;

	//Convert position
	const rp3d::Vector3& other_pos = other.getPosition();
	return_tras.set_position(Core::SVector3(other_pos.x, other_pos.y, other_pos.z));

	//Convert rotation
	const rp3d::Quaternion& rot = other.getOrientation();
	const glm::quat glm_quat(rot.w, rot.x, rot.y, rot.z);
	return_tras.set_rotation(Core::SQuaternion(glm_quat));

	return return_tras;
}

rp3d::Transform ScrapEngine::Physics::ConversionUtils::convert_transform(const Core::STransform& other)
{
	const rp3d::Vector3 pos = convert_vector(other.get_position());

	const Core::SVector3& other_rot = other.get_rotation();
	const rp3d::Quaternion rotation = rp3d::Quaternion::fromEulerAngles(
		other_rot.get_x(),
		other_rot.get_y(),
		other_rot.get_z()
	);

	return rp3d::Transform(pos, rotation);
}

rp3d::Vector3 ScrapEngine::Physics::ConversionUtils::convert_vector(const Core::SVector3& vector)
{
	return rp3d::Vector3(vector.get_x(), vector.get_y(), vector.get_z());
}

ScrapEngine::Core::SVector3 ScrapEngine::Physics::ConversionUtils::convert_vector(const rp3d::Vector3& vector)
{
	return Core::SVector3(vector.x, vector.y, vector.z);
}
