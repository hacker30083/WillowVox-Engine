#include <WillowVoxEngine/Input/Input.h>


namespace WillowVox
{
	Input::Input(GLFWwindow* w)
	{
		window = w;
	}

	Input::~Input()
	{

	}

	bool Input::GetKey(Key key)
	{
		return glfwGetKey(window, key);
	}

	glm::vec2 Input::GetMousePos()
	{
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return glm::vec2(xPos, yPos);
	}

	bool Input::GetMouseButton(int button)
	{
		return glfwGetMouseButton(window, button);
	}

	void Input::DisableMouse()
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (glfwRawMouseMotionSupported())
    		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}

	void Input::EnableMouse()
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (glfwRawMouseMotionSupported())
    		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
	}
}