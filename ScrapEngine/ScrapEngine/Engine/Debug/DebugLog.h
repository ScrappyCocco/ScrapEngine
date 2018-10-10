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

	private:
		//Return a string with the current date and time
		static std::string NowToString();
	};
}

