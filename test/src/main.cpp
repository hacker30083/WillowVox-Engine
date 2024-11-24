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
		tex = new WillowVox::Texture("assets/grass_block_side.png");
		tex->BindTexture(WillowVox::Texture::TEX00);
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