#pragma once

#include <WillowVox/rendering/RenderingAPI.h>
#include <WillowVox/rendering/Window.h>
#include <WillowVox/world/World.h>
#include <iostream>

namespace WillowVox
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		float m_deltaTime;

		World* m_world;

	protected:
        // Client-defined pre-start resource loading
		virtual void LoadAssets() = 0;
		virtual void RegisterBlocks() = 0;

        // Client-defined game logic
		virtual void Start() = 0;
		virtual void Update() = 0;
        // Client-defined rendering logic
		virtual void Render() = 0;
		virtual void ConfigurePostProcessing() = 0;
		virtual void RenderUI() = 0;

		RenderingAPI* _renderingAPI;
		Window* _window;
		const char* _applicationName;

		bool _renderUI = true;
		bool _postProcessingEnabled = true;

	private:
		double _lastFrame;
	};

	Application* CreateApplication();
}