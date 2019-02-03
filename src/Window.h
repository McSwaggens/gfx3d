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

	struct Resolution
	{
		int32_t width;
		int32_t height;
	};

	Resolution GetResolution() const;
	double HeightInWidth() const;
	double WidthInHeight() const;

	void SwapBuffers();
	void BindContext();
	GLFWwindow* GetGLFWWindow();
};
