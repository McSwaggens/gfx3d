#include "Keyboard.h"
#include "Engine.h"

GLFWwindow* g_window;

void SetupKeyboard(GLFWwindow* window)
{
	g_window = window;
}

bool IsKeyPressed(Key key)
{
	return glfwGetKey(g_window, (int)key) == GLFW_PRESS;
}

bool IsKeyDown(Key key)
{
	return glfwGetKey(g_window, (int)key) != GLFW_RELEASE;
}

