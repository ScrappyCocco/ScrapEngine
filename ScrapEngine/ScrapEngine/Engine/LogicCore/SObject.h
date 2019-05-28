#pragma once

#include <string>
#include <Engine/Utility/UsefulTypes.h>
#include <glm/mat4x4.hpp>

namespace ScrapEngine
{
	namespace Core
	{
		class SObject
		{
		private:
			std::string object_name_;
		protected:
			//Generate a Transform Matrix based on the parameter given
			glm::mat4 generate_transform_matrix(const ScrapEngine::Transform& transform) const;

			//Generate a Transform Matrix based on the parameter given, without scaling it
			//This is useful to update child rotation where i can ignore the scale
			glm::mat4 generate_unscaled_transform_matrix(const ScrapEngine::Transform& transform) const;
		public:
			explicit SObject(const std::string& input_object_name = "SObject");
			virtual ~SObject();

			virtual std::string to_string() const;
		};
	}
}
