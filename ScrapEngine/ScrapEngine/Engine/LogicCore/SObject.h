#pragma once

#include <string>

namespace ScrapEngine {
	class SObject
	{
	private:
		std::string object_name;
	public:
		SObject(const std::string& input_object_name = "SObject");
		virtual ~SObject() = 0;

		virtual std::string toString() const;
	};
}

