#pragma once

namespace WillowVox
{
	class Logger
	{
	public:
		// Client
		static void Log(const char* msg);
		// Engine
		static void EngineLog(const char* msg);
	};
}