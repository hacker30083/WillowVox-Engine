#pragma once

#include <WillowVoxEngine/Version.h>

extern WillowVox::Application* WillowVox::CreateApplication();

int main(int argc, char** argv)
{
	WillowVox::Logger::EngineLog("WillowVox Engine\n");
	WillowVox::Logger::Log("Client\n");
	auto app = WillowVox::CreateApplication();
	app->Run();
	delete app;
}