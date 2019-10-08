#pragma once
#include <glm/vec3.hpp>

namespace ScrapEngine
{
	namespace Core
	{
		class SVector3
		{
		private:
			glm::vec3 vec3_{};
		public:
			SVector3();
			explicit SVector3(glm::vec3 input);
			SVector3(float x, float y, float z);
			SVector3(const SVector3& other) = default;
			SVector3& operator=(const SVector3& other) = default;
			SVector3(SVector3&&) = default;
			SVector3& operator=(SVector3&&) = default;
			~SVector3() = default;

			SVector3 operator+(const SVector3& other) const;
			SVector3 operator-(const SVector3& other) const;
			SVector3 operator*(const SVector3& other) const;
			SVector3 operator*(float value) const;
			//explicit conversion operator to glm::vec3
			explicit operator glm::vec3() const;

			float get_x() const;
			float get_y() const;
			float get_z() const;
			void set_x(float x);
			void set_y(float y);
			void set_z(float z);
			float get_max_value() const;
			SVector3 get_vector() const;
			glm::vec3 get_glm_vector() const;
			void set_vector(const SVector3& other);

			SVector3 normalize() const;
			float length() const;
			float distance(const SVector3& other) const;

			static SVector3 cross_product(const SVector3& a, const SVector3& b);
			static float dot(const SVector3& a, const SVector3& b);
		};
	}
}
