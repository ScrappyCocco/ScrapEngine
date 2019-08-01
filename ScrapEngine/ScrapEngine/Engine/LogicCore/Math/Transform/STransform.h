#pragma once
#include <Engine/LogicCore/Math/Quaternion/SQuaternion.h>

namespace ScrapEngine
{
	namespace Core
	{
		class STransform
		{
		private:
			SVector3 position_;
			SVector3 rotation_;
			SQuaternion quaternion_rotation_;
			SVector3 scale_;
		public:
			explicit STransform(const SVector3& position = SVector3(), const SVector3& rotation = SVector3(),
			                    const SVector3& scale = SVector3(1, 1, 1));
			STransform(const STransform& other) = default;
			STransform& operator=(const STransform& other) = default;
			STransform(STransform&&) = default;
			STransform& operator=(STransform&&) = default;
			~STransform() = default;

			SVector3 get_position() const;
			SVector3 get_rotation() const;
			SQuaternion get_quat_rotation() const;
			SVector3 get_scale() const;

			void set_position(const SVector3& new_position);
			void set_rotation(const SVector3& new_rotation);
			void set_rotation(const SQuaternion& new_rotation);
			void set_quat_rotation(const SQuaternion& new_rotation);
			void add_rotation(const SVector3& rotation);
			void set_scale(const SVector3& new_scale);
		};
	}
}
