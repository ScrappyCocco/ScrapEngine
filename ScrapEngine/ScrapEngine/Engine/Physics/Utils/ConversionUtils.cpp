#include <Engine/Physics/Utils/ConversionUtils.h>

ScrapEngine::Core::STransform ScrapEngine::Physics::ConversionUtils::convert_transform(const rp3d::Transform& other)
{
	Core::STransform return_tras;

	//Convert position
	return_tras.set_position(convert_vector(other.getPosition()));

	//Convert rotation
	return_tras.set_rotation(convert_quaternion(other.getOrientation()));

	return return_tras;
}

rp3d::Transform ScrapEngine::Physics::ConversionUtils::convert_transform(const Core::STransform& other)
{
	//Convert position
	const rp3d::Vector3 pos = convert_vector(other.get_position());

	//Convert rotation
	const rp3d::Quaternion rotation(convert_quaternion(other.get_quat_rotation()));

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

ScrapEngine::Core::SQuaternion ScrapEngine::Physics::ConversionUtils::convert_quaternion(const rp3d::Quaternion& quat)
{
	return Core::SQuaternion(quat.x, quat.y, quat.z, quat.w);
}

rp3d::Quaternion ScrapEngine::Physics::ConversionUtils::convert_quaternion(const Core::SQuaternion& quat)
{
	return rp3d::Quaternion(quat.get_x(), quat.get_y(), quat.get_z(), quat.get_w());
}
