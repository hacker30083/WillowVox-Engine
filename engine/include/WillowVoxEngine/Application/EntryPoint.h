#pragma once

#include <WillowVoxEngine/Version.h>

extern WillowVox::Application* WillowVox::CreateApplication();

int main(int argc, char** argv)
{
	WillowVox::Logger::EngineLog("WillowVox Engine %s", PROJECT_VERSION);
	WillowVox::Logger::Log("Client");
	auto app = WillowVox::CreateApplication();
	app->Run();
	delete app;
	WillowVox::Logger::CloseLogger();
}