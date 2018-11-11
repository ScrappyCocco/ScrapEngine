#pragma once

#include <iostream>
#include <glm/glm.hpp>

namespace ScrapEngine {
	class DebugLog
	{
	public:
		//Print the message to console log with time
		static void printToConsoleLog(const std::string&);

		static void printToConsoleLog(const glm::vec3&);

		static void printExceptionToConsoleLog(const std::string& messageSeverity, const std::string& exceptionString);

	private:
		//Return a string with the current date and time
		static std::string NowToString();
	};
}
