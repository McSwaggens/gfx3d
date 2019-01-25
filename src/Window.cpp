#include "Window.h"

void Framebuffer_SizeChanged_Callback(GLFWwindow* g_window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(const std::string& name, uint32_t width, uint32_t height)
{
	m_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	glfwSetFramebufferSizeCallback(m_window, Framebuffer_SizeChanged_Callback);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Window::BindContext()
{
	glfwMakeContextCurrent(m_window);
}

GLFWwindow* Window::GetGLFWWindow()
{
	return m_window;
}

