#pragma once
#include <Engine/LogicCore/Math/Vector/SVector3.h>
#include <glm/ext/quaternion_float.hpp>

namespace ScrapEngine
{
	namespace Core
	{
		class SQuaternion
		{
		private:
			glm::quat quat_{};

			SVector3 rotate_vector(const SVector3& other) const;
			SVector3 unrotate_vector(const SVector3& other) const;
		public:
			SQuaternion();
			SQuaternion(float x, float y, float z, float w);
			static SQuaternion identity();
			explicit SQuaternion(glm::quat input);
			explicit SQuaternion(const SVector3& euler_angles);
			SQuaternion(const SQuaternion& other) = default;
			SQuaternion& operator=(const SQuaternion& other) = default;
			SQuaternion(SQuaternion&&) = default;
			SQuaternion& operator=(SQuaternion&&) = default;
			~SQuaternion() = default;

			SQuaternion operator*(const SQuaternion& other) const;

			SVector3 get_axis_x() const;
			SVector3 get_axis_y() const;
			SVector3 get_axis_z() const;

			float get_x() const;
			float get_y() const;
			float get_z() const;
			float get_w() const;

			SQuaternion get_inverse() const;

			SVector3 get_forward_vector() const;
			SVector3 get_right_vector() const;
			SVector3 get_up_vector() const;

			SVector3 to_euler_angles() const;

			glm::quat get_glm_quat() const;
		};
	}
}
