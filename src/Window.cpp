#include "Window.h"

void Framebuffer_SizeChanged_Callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window_SizeChanged_Callback(GLFWwindow* window, int width, int height)
{
	// FIXME: Unused because there isn't a very-
	// 	good way to get the propper Window class.
}

Window::Window(const std::string& name, uint32_t width, uint32_t height)
{
	m_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	glfwSetFramebufferSizeCallback(m_window, Framebuffer_SizeChanged_Callback);
	glfwSetWindowSizeCallback(m_window, Window_SizeChanged_Callback);
}

Window::Resolution Window::GetResolution() const
{
	Window::Resolution res;
	glfwGetWindowSize(m_window, &res.width, &res.height);
	return res;
}

double Window::WidthInHeight() const
{
	Window::Resolution res = GetResolution();
	return (double)res.width / (double)res.height;
}

double Window::HeightInWidth() const
{
	return 1 / WidthInHeight();
}

Window::~Window()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
	}
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

