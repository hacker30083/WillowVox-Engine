#include <WillowVoxEngine/Core/Logger.h>

#include <iostream>

namespace WillowVox
{
	void Logger::Log(const char* msg)
	{
		std::cout << "[App] " << msg;
	}

	void Logger::EngineLog(const char* msg)
	{
		std::cout << "[WV Engine] " << msg;
	}
}