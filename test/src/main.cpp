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
	WillowVox::Texture* tex;

	bool mouseDisabled = false;

	void Start() override
	{
		tex = new WillowVox::Texture("assets/grass_block_side.png");
		tex->BindTexture(WillowVox::Texture::TEX00);

		input->keyPressEventDispatcher.RegisterListener([this](WillowVox::KeyPressEvent& e) {
			if (e.key != WillowVox::ESC)
				return;

			this->mouseDisabled = !this->mouseDisabled;
			if (this->mouseDisabled)
				this->input->DisableMouse();
			else
				this->input->EnableMouse();
		});
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