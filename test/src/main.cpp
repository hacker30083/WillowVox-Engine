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
	WillowVox::Shader* shader;
	WillowVox::MeshRenderer<WillowVox::Vertex>* mr;
	WillowVox::Texture* tex;

	glm::vec3 squarePos;

	void Start() override
	{
		shader = new WillowVox::Shader("assets/vert.glsl", "assets/frag.glsl");
		shader->Use();
		shader->SetVec3("color", 0.5f, 0.5f, 1.0f);

		mr = new WillowVox::MeshRenderer<WillowVox::Vertex>(*shader);

		WillowVox::Vertex vertices[] = {
			{ { -1.0f, -1.0f, -5.0f }, { 0.0f, 0.0f } },
			{ {  1.0f, -1.0f, -5.0f }, { 1.0f, 0.0f } },
			{ { -1.0f,  1.0f, -5.0f }, { 0.0f, 1.0f } },
			{ {  1.0f,  1.0f, -5.0f }, { 1.0f, 1.0f } },
		};
	
		uint32_t indices[] = {
			0, 1, 3,
			0, 2, 3
		};

		WillowVox::Mesh<WillowVox::Vertex>* mesh = new WillowVox::Mesh<WillowVox::Vertex>();
		mesh->SetMeshData(vertices, 4, indices, 6);

		tex = new WillowVox::Texture("assets/grass_block_side.png");
		tex->BindTexture(WillowVox::Texture::TEX00);

		mr->SetMesh(mesh, true);

		squarePos = glm::vec3(0);

		input->inputEventDispatcher.RegisterListener(WillowVox::Event::Type::MouseScroll, [this](WillowVox::Event& e) {
			WillowVox::Logger::Log("Mouse scrolled\n");
		});
	}

	void Update() override
	{
		if (input->GetKey(WillowVox::W))
			squarePos.y += 2 * deltaTime;
		if (input->GetKey(WillowVox::S))
			squarePos.y -= 2 * deltaTime;
		if (input->GetKey(WillowVox::A))
			squarePos.x -= 2 * deltaTime;
		if (input->GetKey(WillowVox::D))
			squarePos.x += 2 * deltaTime;
	}

	void Render() override
	{
		glm::mat4 view = mainCamera->GetViewMatrix();
		glm::mat4 projection = mainCamera->GetProjectionMatrix();
		shader->Use();
		shader->SetMat4("view", view);
		shader->SetMat4("projection", projection);
		shader->SetVec3("model", squarePos);

		mr->Render();
	}
};

WillowVox::Application* WillowVox::CreateApplication()
{
	return new WVTest();
}