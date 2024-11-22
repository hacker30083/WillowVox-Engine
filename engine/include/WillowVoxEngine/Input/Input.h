#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <WillowVoxEngine/Events/EventDispatcher.h>

namespace WillowVox
{
	enum Key
	{
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		KEY_0 = GLFW_KEY_0,
		KEY_1 = GLFW_KEY_1,
		KEY_2 = GLFW_KEY_2,
		KEY_3 = GLFW_KEY_3,
		KEY_4 = GLFW_KEY_4,
		KEY_5 = GLFW_KEY_5,
		KEY_6 = GLFW_KEY_6,
		KEY_7 = GLFW_KEY_7,
		KEY_8 = GLFW_KEY_8,
		KEY_9 = GLFW_KEY_9,
		NUMPAD_0 = GLFW_KEY_KP_0,
		NUMPAD_1 = GLFW_KEY_KP_1,
		NUMPAD_2 = GLFW_KEY_KP_2,
		NUMPAD_3 = GLFW_KEY_KP_3,
		NUMPAD_4 = GLFW_KEY_KP_4,
		NUMPAD_5 = GLFW_KEY_KP_5,
		NUMPAD_6 = GLFW_KEY_KP_6,
		NUMPAD_7 = GLFW_KEY_KP_7,
		NUMPAD_8 = GLFW_KEY_KP_8,
		NUMPAD_9 = GLFW_KEY_KP_9,
		ESC = GLFW_KEY_ESCAPE,
		L_SHIFT = GLFW_KEY_LEFT_SHIFT,
		R_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		L_CONTROL = GLFW_KEY_LEFT_CONTROL,
		R_CONTROL = GLFW_KEY_RIGHT_CONTROL,
		TAB = GLFW_KEY_TAB,
		BACKSPACE = GLFW_KEY_BACKSPACE,
		BACKSLASH = GLFW_KEY_BACKSLASH,
		MINUS = GLFW_KEY_MINUS,
		EQUAL = GLFW_KEY_EQUAL,
		LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
		RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
		SEMICOLON = GLFW_KEY_SEMICOLON,
		APOSTROPHE = GLFW_KEY_APOSTROPHE,
		COMMA = GLFW_KEY_COMMA,
		PERIOD = GLFW_KEY_PERIOD,
		FORWARD_SLASH = GLFW_KEY_SLASH,
		ENTER = GLFW_KEY_ENTER,
		L_ALT = GLFW_KEY_LEFT_ALT,
		R_ALT = GLFW_KEY_RIGHT_ALT,
		SPACE = GLFW_KEY_SPACE,
		ARROW_KEY_UP = GLFW_KEY_UP,
		ARROW_KEY_DOWN = GLFW_KEY_DOWN,
		ARROW_KEY_LEFT = GLFW_KEY_LEFT,
		ARROW_KEY_RIGHT = GLFW_KEY_RIGHT,
		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,
		BACKTICK = GLFW_KEY_GRAVE_ACCENT,
	};

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

		EventDispatcher inputEventDispatcher;

	private:
		GLFWwindow* window;
	};
}