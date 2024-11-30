#include <WillowVoxEngine/WillowVox.h>
#include <TestWorld.h>

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
	WillowVox::Texture* tex;

	void LoadAssets() override
	{

	}

	void RegisterBlocks() override
	{
		WillowVox::Blocks::RegisterBlock({ 1, 1, 0, 0, 1, 0, WillowVox::Block::SOLID, "Grass Block"});
		WillowVox::Blocks::RegisterBlock({ 1, 2, WillowVox::Block::BILLBOARD, "Grass"});
	}

	void InitWorld() override
	{
		loadedWorld = new TestWorld();
	}

	void Start() override
	{

	}

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