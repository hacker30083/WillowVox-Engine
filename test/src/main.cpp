#pragma once

#include <WillowVox/core/Application.h>
#include <WillowVox/rendering/Mesh.h>
#include <WillowVox/rendering/BaseMaterial.h>
#include <WillowVox/rendering/Camera.h>
#include <WillowVox/rendering/Texture.h>
#include <WillowVox/core/EntryPoint.h>
#include <WillowVox/core/Logger.h>
#include <WillowVox/rendering/engine-default/TextureMaterial.h>
#include <WillowVox/rendering/engine-default/Vertex.h>
#include <WillowVox/rendering/engine-default/ChunkVertex.h>
#include <WillowVox/rendering/engine-default/ChunkSolidMaterial.h>
#include <WillowVox/rendering/engine-default/TextureMaterial.h>
#include <WillowVox/physics/Physics.h>
#include <WillowVox/resources/Blocks.h>
#include <TestGame.h>
#include <TestWorld.h>
#include <imgui.h>
#include <cstdint>

using namespace WillowVox;

namespace TestGame
{
	class TestGameApp : public Application
	{
	public:
		TestGameApp()
		{
			_applicationName = "Test Game";
		}

		void LoadAssets() override
		{

		}

		void RegisterBlocks() override
		{
			Blocks::RegisterBlock({ 1, 1, 0, 0, 1, 0, Block::SOLID, "Grass Block" });
			Blocks::RegisterBlock({ 1, 2, Block::BILLBOARD, "Grass" });
			Blocks::RegisterBlock({ 0, 4, Block::LIQUID, "Water" });
		}

		void Start() override
		{
			Logger::Log("Started Test Game %s", GAME_VERSION);

			_window->SetBackgroundColor(0.6f, 0.8f, 1.0f, 1.0f);
			_renderingAPI->SetCullFace(true);
			_renderingAPI->SetDepthTest(true);

			_camera = new WillowVox::Camera(_window);

			_window->SetMouseDisabled(true);

			m_world = new TestWorld(_camera);

			_window->MouseScrollEventDispatcher.RegisterListener([this](MouseScrollEvent& e) {
				if (this->_paused)
					return;

				this->_moveSpeed += (float)e.m_yOffset;
				if (this->_moveSpeed < 0)
					this->_moveSpeed = 0;
			});

			_test = new PostProcessingShader(_renderingAPI->CreateShader("assets/shaders/post-processing/test_vert.glsl", "assets/shaders/post-processing/test_frag.glsl"), false);

			_window->AddPostProcessingShader(_test);
		}

		void Update() override
		{
			if (_window->KeyDown(Key::ESC))
			{
				if (!_escPressed)
				{
					_paused = !_paused;
					_window->SetMouseDisabled(!_paused);
					_escPressed = true;
					_firstFrame = true;
				}
			}
			else if (_escPressed)
			{
				_escPressed = false;
			}

			if (_window->KeyDown(Key::F1))
			{
				if (!_f1Pressed)
				{
					_renderUI = !_renderUI;
					_f1Pressed = true;
				}
			}
			else if (_f1Pressed)
				_f1Pressed = false;

			if (_paused)
				return;

			// Camera movement
			if (_window->KeyDown(Key::W))
			{
				if (_window->KeyDown(Key::SPACE))
				{
					glm::vec3 dir = _camera->Front();
					dir.y = 0;
					dir = glm::normalize(dir);
					_camera->position += dir * _moveSpeed * m_deltaTime;
				}
				else
					_camera->position += _camera->Front() * _moveSpeed * m_deltaTime;
			}
			if (_window->KeyDown(Key::S))
			{
				if (_window->KeyDown(Key::SPACE))
				{
					glm::vec3 dir = _camera->Front();
					dir.y = 0;
					dir = glm::normalize(dir);
					_camera->position += -dir * _moveSpeed * m_deltaTime;
				}
				else
					_camera->position += -_camera->Front() * _moveSpeed * m_deltaTime;
			}
			if (_window->KeyDown(Key::A))
				_camera->position += -_camera->Right() * _moveSpeed * m_deltaTime;
			if (_window->KeyDown(Key::D))
				_camera->position += _camera->Right() * _moveSpeed * m_deltaTime;
			if (_window->KeyDown(Key::E))
				_camera->position += _camera->Up() * _moveSpeed * m_deltaTime;
			if (_window->KeyDown(Key::Q))
				_camera->position += -_camera->Up() * _moveSpeed * m_deltaTime;

			auto mouseDiff = _window->GetMouseMovement();

			if (_firstFrame)
				_firstFrame = false;
			else
			{
				_camera->direction.y += mouseDiff.x * 0.1f;
				_camera->direction.x -= mouseDiff.y * 0.1f;
				if (_camera->direction.x > 89.0f)
					_camera->direction.x = 89.0f;
				else if (_camera->direction.x < -89.0f)
					_camera->direction.x = -89.0f;
			}

			// Clicking
			if (_window->MouseButtonDown(0))
			{
				if (!_leftClick)
				{
					_leftClick = true;

					// Left click started
					auto result = Physics::Raycast(_camera->position, _camera->Front(), 10.0f);
					if (result.hit)
					{
						result.chunk->SetBlock(result.localBlockX, result.localBlockY, result.localBlockZ, 0);
					}
				}
			}
			else if (_leftClick)
				_leftClick = false;

			if (_window->MouseButtonDown(2))
			{
				auto result = Physics::Raycast(_camera->position, _camera->Front(), 10.0f);
				if (!result.hit)
					return;

				_selectedBlock = result.chunk->GetBlockIdAtPos(result.localBlockX, result.localBlockY, result.localBlockZ);
			}

			if (_window->MouseButtonDown(1))
			{
				if (!_rightClick)
				{
					_rightClick = true;

					auto result = Physics::Raycast(_camera->position, _camera->Front(), 10.0f);

					float distX = result.hitPos.x - (result.blockX + .5f);
					float distY = result.hitPos.y - (result.blockY + .5f);
					float distZ = result.hitPos.z - (result.blockZ + .5f);

					int blockX = result.blockX;
					int blockY = result.blockY;
					int blockZ = result.blockZ;

					// Choose face to place on
					if (abs(distX) > abs(distY) && abs(distX) > abs(distZ))
						blockX += (distX > 0 ? 1 : -1);
					else if (abs(distY) > abs(distX) && abs(distY) > abs(distZ))
						blockY += (distY > 0 ? 1 : -1);
					else
						blockZ += (distZ > 0 ? 1 : -1);

					int chunkX = blockX < 0 ? floorf(blockX / (float)CHUNK_SIZE) : blockX / (int)CHUNK_SIZE;
					int chunkY = blockY < 0 ? floorf(blockY / (float)CHUNK_SIZE) : blockY / (int)CHUNK_SIZE;
					int chunkZ = blockZ < 0 ? floorf(blockZ / (float)CHUNK_SIZE) : blockZ / (int)CHUNK_SIZE;

					int localBlockX = blockX - (chunkX * CHUNK_SIZE);
					int localBlockY = blockY - (chunkY * CHUNK_SIZE);
					int localBlockZ = blockZ - (chunkZ * CHUNK_SIZE);

					auto chunk = ChunkManager::m_instance->GetChunk(chunkX, chunkY, chunkZ);
					if (chunk == nullptr)
						return;

					uint16_t blockToReplace = chunk->GetBlockIdAtPos(localBlockX, localBlockY, localBlockZ);
					if (blockToReplace == 0 || Blocks::GetBlock(blockToReplace).blockType == Block::LIQUID)
						chunk->SetBlock(localBlockX, localBlockY, localBlockZ, _selectedBlock);
				}
			}
			else if (_rightClick)
				_rightClick = false;
		}

		void Render() override
		{

		}

		void ConfigurePostProcessing() override
		{
			_test->enabled = ChunkManager::m_instance->GetBlockIdAtPos(_camera->position) == 3;
		}

		void RenderUI() override
		{
			ImGui::Begin("Test Game", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Text("Yo dude");
		}

	private:
		Camera* _camera;

		float _moveSpeed = 10.0f;
		int _selectedBlock = 1;
		PostProcessingShader* _test;

		bool _firstFrame = true;
		bool _escPressed = false;
		bool _paused = false;
		bool _leftClick = false;
		bool _rightClick = false;
		bool _f1Pressed = false;
	};
}


WillowVox::Application* WillowVox::CreateApplication()
{
	return new TestGame::TestGameApp();
}