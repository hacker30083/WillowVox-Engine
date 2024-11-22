#pragma once

#include <WillowVoxEngine/Version.h>
#include <iostream>
#include <sstream>

extern WillowVox::Application* WillowVox::CreateApplication();

struct Vec3
{
	float x, y, z;

	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

int main(int argc, char** argv)
{
	WillowVox::Logger::EngineLog("WillowVox Engine %s", PROJECT_VERSION);
	WillowVox::Logger::Log("Client");
	auto app = WillowVox::CreateApplication();
	app->Run();
	delete app;
}