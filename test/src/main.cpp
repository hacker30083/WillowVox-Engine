#include <WillowVoxEngine/WillowVox.h>

class WVTest : public WillowVox::Application
{
public:
	WVTest()
	{

	}

	~WVTest()
	{

	}

protected:
	void Update() override
	{
		//WillowVox::Logger::Log("Update\n");
	}

	void Render() override
	{
		//WillowVox::Logger::Log("Render\n");
	}
};

WillowVox::Application* WillowVox::CreateApplication()
{
	return new WVTest();
}