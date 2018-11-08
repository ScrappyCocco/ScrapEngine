#pragma once

#include <iostream>
#include <glm/glm.hpp>

namespace ScrapEngine {
	class DebugLog
	{
	public:
		//Print the message to console log with time
		static void printToConsoleLog(std::string);

		static void printToConsoleLog(glm::vec3);

		static void printExceptionToConsoleLog(std::string messageSeverity, std::string exceptionString);

	private:
		//Return a string with the current date and time
		static std::string NowToString();
	};
}

