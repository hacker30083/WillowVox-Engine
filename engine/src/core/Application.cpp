#include <WillowVox/core/Application.h>

#include <WillowVox/rendering/RenderingAPI.h>
#include <WillowVox/rendering/Window.h>
#include <WillowVox/resources/Blocks.h>
#include <WillowVox/WillowVox.h>
#include <iostream>
#include <thread>
#include <chrono>

namespace WillowVox
{
    Application::Application()
    {
        Logger::EngineLog("Using WillowVox Engine %s", ENGINE_VERSION);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        // Init rendering API and window
        _renderingAPI = RenderingAPI::GetRenderingAPI();
        _window = _renderingAPI->CreateWindow(_defaultWindowWidth, _defaultWindowHeight, _applicationName);

        // Load assets and resources
        LoadAssets();
        Blocks::RegisterBlock({0, 0, Block::TRANSPARENT, "Air"}); // Define air (empty block)
        RegisterBlocks();

        // Pre-game loop start logic
        Start(); // Must define world in client
        m_world->Start();

        // Game loop
        while (!_window->ShouldClose())
        {
            // Calculate deltaTime and frame start time
            float frameStartTime = _renderingAPI->GetTime();
            float currentFrame = frameStartTime;
            m_deltaTime = currentFrame - _lastFrame;
            _lastFrame = currentFrame;

            _window->FrameStart();

            // Client-defined update and render logic
            Update();
            m_world->Update();
            Render();
            m_world->Render();

            // Post processing
            if (_postProcessingEnabled)
            {
                ConfigurePostProcessing();
                _window->PostProcessingStart();
            }
            _window->PostProcessingEnd();

            // UI
            if (_renderUI)
            {
                _window->UIStart();
                RenderUI();
                _window->UIEnd();
            }

            _window->FrameEnd();

            // FPS limiting
            if (_fpsLockEnabled && _targetFPS > 0)
            {
                float frameDuration = _renderingAPI->GetTime() - frameStartTime;
                float targetFrameTime = 1.0f / _targetFPS;

                if (frameDuration < targetFrameTime)
                {
                    float sleepTime = targetFrameTime - frameDuration;
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepTime * 1000)));
                }
            }
        }
    }

    void Application::SetTargetFPS(int targetFPS)
    {
        _targetFPS = targetFPS;
    }

    int Application::GetTargetFPS() const
    {
        return _targetFPS;
    }

    void Application::SetFPSLockEnabled(bool enabled)
    {
        _fpsLockEnabled = enabled;
    }

    bool Application::IsFPSLockEnabled() const
    {
        return _fpsLockEnabled;
    }

    ImGuiContext *Application::GetImGuiContext()
    {
        return ImGui::GetCurrentContext();
    }
}
