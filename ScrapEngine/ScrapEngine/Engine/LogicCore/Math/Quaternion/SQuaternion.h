#pragma once
#include "Engine/LogicCore/Math/Vector/SVector3.h"
#include <glm/ext/quaternion_float.hpp>

namespace ScrapEngine
{
	namespace Core
	{
		class SQuaternion
		{
		private:
			glm::quat quat_{};

			explicit SQuaternion(const glm::quat input);
			SVector3 rotate_vector(const SVector3& other) const;
			SVector3 unrotate_vector(const SVector3& other) const;
		public:
			SQuaternion();
			SQuaternion(const float x, const float y, const float z, const float w);
			explicit SQuaternion(const SVector3& euler_angles);
			SQuaternion(const SQuaternion& other) = default;
			SQuaternion& operator=(const SQuaternion& other) = default;
			SQuaternion(SQuaternion&&) = default;
			SQuaternion& operator=(SQuaternion&&) = default;
			~SQuaternion() = default;

			SVector3 get_axis_x() const;
			SVector3 get_axis_y() const;
			SVector3 get_axis_z() const;

			SVector3 get_forward_vector() const;
			SVector3 get_right_vector() const;
			SVector3 get_up_vector() const;
		};
	}
}
