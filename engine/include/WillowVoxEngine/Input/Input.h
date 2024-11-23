#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <WillowVoxEngine/Input/Key.h>
#include <WillowVoxEngine/Events/EventDispatcher.h>
#include <WillowVoxEngine/Events/MouseScrollEvent.h>
#include <WillowVoxEngine/Events/KeyPressEvent.h>
#include <WillowVoxEngine/Events/KeyReleaseEvent.h>
#include <WillowVoxEngine/Events/MouseMoveEvent.h>
#include <WillowVoxEngine/Events/MouseClickEvent.h>
#include <WillowVoxEngine/Events/MouseReleaseEvent.h>

namespace WillowVox
{
	class Input
	{
	public:
		Input(GLFWwindow* w);
		~Input();

		bool GetKey(Key key);
		glm::vec2 GetMousePos();
		bool GetMouseButton(int button);

		void DisableMouse();
		void EnableMouse();

		EventDispatcher<KeyPressEvent> keyPressEventDispatcher;
		EventDispatcher<KeyReleaseEvent> keyReleaseEventDispatcher;
		EventDispatcher<MouseClickEvent> mouseClickEventDispatcher;
		EventDispatcher<MouseReleaseEvent> mouseReleaseEventDispatcher;
		EventDispatcher<MouseMoveEvent> mouseMoveEventDispatcher;
		EventDispatcher<MouseScrollEvent> mouseScrollEventDispatcher;

	private:
		GLFWwindow* window;
	};
}