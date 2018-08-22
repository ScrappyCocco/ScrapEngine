#pragma once

#include <iostream>

namespace ScrapEngine {

	class DebugLog
	{
	public:
		//Print the message to console log with time
		static void printToConsoleLog(std::string);

	private:
		//Return a string with the current date and time
		static std::string NowToString();
	};
}

