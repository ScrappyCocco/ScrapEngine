#pragma once

#include <string>

namespace ScrapEngine
{
	namespace Core
	{
		class SObject
		{
		private:
			std::string object_name_;
		public:
			explicit SObject(const std::string& input_object_name = "SObject");
			virtual ~SObject();

			virtual std::string to_string() const;
		};
	}
}
