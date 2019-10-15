#pragma once

#include <Engine/Physics/PhysicsInclude.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class ConversionUtils
		{
		public:
			static Core::STransform convert_transform(const rp3d::Transform& other);
			static rp3d::Transform convert_transform(const Core::STransform& other);

			static rp3d::Vector3 convert_vector(const Core::SVector3& vector);
			static Core::SVector3 convert_vector(const rp3d::Vector3& vector);

			static Core::SQuaternion convert_quaternion(const rp3d::Quaternion& quat);
			static rp3d::Quaternion convert_quaternion(const Core::SQuaternion& quat);
		};
	}
}
