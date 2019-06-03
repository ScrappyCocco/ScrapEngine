#pragma once

#include <iostream>
#include <glm/mat4x4.hpp>
#include <Engine/LogicCore/Math/Vector/SVector3.h>

namespace ScrapEngine {
	namespace Core {
		class SVector3;
	}
}

namespace ScrapEngine
{
	namespace Debug
	{
		class DebugLog
		{
		public:
			//Print the message to console log with time
			static void print_to_console_log(const std::string&);

			//Print the vector to console log with time
			static void print_to_console_log(const glm::vec3&);

			//Print the engine vector to console log with time
			static void print_to_console_log(const Core::SVector3&);

			//Print the matrix to console log with time
			static void print_to_console_log(const glm::mat4&);

			//Print the error to console
			static void print_exception_to_console_log(const std::string& message_severity,
			                                           const std::string& exception_string);

		private:
			//Return a string with the current date and time
			static std::string now_to_string();
		};
	}
}
