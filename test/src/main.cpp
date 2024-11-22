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

	}

	void Render() override
	{
		
	}
};

WillowVox::Application* WillowVox::CreateApplication()
{
	return new WVTest();
}