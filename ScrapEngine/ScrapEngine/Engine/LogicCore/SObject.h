#pragma once

#include <string>
#include <Engine/Utility/UsefulTypes.h>

namespace ScrapEngine
{
	namespace Core
	{
		class SObject
		{
		private:
			std::string object_name_;
		protected:
			glm::mat4 generate_transform_matrix(const ScrapEngine::Transform& transform) const;
		public:
			explicit SObject(const std::string& input_object_name = "SObject");
			virtual ~SObject();

			virtual std::string to_string() const;
		};
	}
}
