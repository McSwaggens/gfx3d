#pragma once
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

class Window final
{
private:
	GLFWwindow* m_window = nullptr;
public:
	Window(const std::string& name, uint32_t width, uint32_t height);
	~Window();

	void SwapBuffers();
	void BindContext();
	GLFWwindow* GetGLFWWindow();
};
