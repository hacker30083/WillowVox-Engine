#pragma once

#include <chrono>
#include <ctime>
#include <iostream>

#define LOG_COLOR_RESET        "\x1b[0m"
#define LOG_COLOR_APP_WARN     "\x1b[93m"
#define LOG_COLOR_APP_ERROR    "\x1b[91m"
#define LOG_COLOR_ENGINE_LOG   "\x1b[32m"
#define LOG_COLOR_ENGINE_WARN  "\x1b[33m"
#define LOG_COLOR_ENGINE_ERROR "\x1b[41m"

namespace WillowVox
{
	class Logger
	{
	public:
		// Client
		template <typename... Args>
		static void Log(const char* msg, Args... args)
		{
			std::time_t t = std::time(nullptr);
			std::tm* now = std::localtime(&t);
			printf(LOG_COLOR_RESET "[%d:%d:%d App] ", now->tm_hour, now->tm_min, now->tm_sec);
			printf(msg, args...);
			printf("\n");
		}

		template <typename... Args>
		static void Warn(const char* msg, Args... args)
		{
			std::time_t t = std::time(nullptr);
			std::tm* now = std::localtime(&t);
			printf(LOG_COLOR_APP_WARN "[%d:%d:%d App] WARN: ", now->tm_hour, now->tm_min, now->tm_sec);
			printf(msg, args...);
			printf(LOG_COLOR_RESET "\n");
		}

		template <typename... Args>
		static void Error(const char* msg, Args... args)
		{
			std::time_t t = std::time(nullptr);
			std::tm* now = std::localtime(&t);
			printf(LOG_COLOR_APP_ERROR "[%d:%d:%d App] ERROR: ", now->tm_hour, now->tm_min, now->tm_sec);
			printf(msg, args...);
			printf(LOG_COLOR_RESET "\n");
		}

		// Engine
		template <typename... Args>
		static void EngineLog(const char* msg, Args... args)
		{
			std::time_t t = std::time(nullptr);
			std::tm* now = std::localtime(&t);
			printf(LOG_COLOR_ENGINE_LOG "[%d:%d:%d Engine] ", now->tm_hour, now->tm_min, now->tm_sec);
			printf(msg, args...);
			printf(LOG_COLOR_RESET "\n");
		}

		template <typename... Args>
		static void EngineWarn(const char* msg, Args... args)
		{
			std::time_t t = std::time(nullptr);
			std::tm* now = std::localtime(&t);
			printf(LOG_COLOR_ENGINE_WARN "[%d:%d:%d Engine] WARN: ", now->tm_hour, now->tm_min, now->tm_sec);
			printf(msg, args...);
			printf(LOG_COLOR_RESET "\n");
		}

		template <typename... Args>
		static void EngineError(const char* msg, Args... args)
		{
			std::time_t t = std::time(nullptr);
			std::tm* now = std::localtime(&t);
			printf(LOG_COLOR_ENGINE_ERROR "[%d:%d:%d Engine] ERROR: ", now->tm_hour, now->tm_min, now->tm_sec);
			printf(msg, args...);
			printf(LOG_COLOR_RESET "\n");
		}
	};
}