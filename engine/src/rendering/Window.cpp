#include <WillowVox/rendering/Window.h>

namespace WillowVox
{
	void Window::AddPostProcessingShader(PostProcessingShader* shader)
	{
		_postProcessingShaders.push_back(shader);
	}
}