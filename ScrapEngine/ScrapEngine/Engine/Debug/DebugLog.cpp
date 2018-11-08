#include "DebugLog.h"
#include <iomanip>
#include <chrono>
#include <string>

void ScrapEngine::DebugLog::printToConsoleLog(std::string logString)
{
	std::cout << NowToString().c_str() << logString.c_str() << std::endl;
}

void ScrapEngine::DebugLog::printToConsoleLog(glm::vec3 vector)
{
	std::cout << NowToString().c_str() << "Vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")" << std::endl;
}

void ScrapEngine::DebugLog::printExceptionToConsoleLog(std::string messageSeverity, std::string exceptionString)
{
	std::cout << std::endl << NowToString().c_str() << messageSeverity << exceptionString << std::endl << std::endl;
}

std::string ScrapEngine::DebugLog::NowToString()
{
	struct tm timeinfo;
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_s(&timeinfo, &now);

	return "[" + std::to_string(timeinfo.tm_mday) + "-" + std::to_string(timeinfo.tm_mon + 1) + "-" + std::to_string(timeinfo.tm_year + 1900)
		+ " " + std::to_string(timeinfo.tm_hour) + ":" + std::to_string(timeinfo.tm_min) + ":" + std::to_string(timeinfo.tm_sec) + "]";
}
