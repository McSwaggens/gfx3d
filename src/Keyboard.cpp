#include "Keyboard.h"
#include <algorithm>
#include <utility>

KeyboardState kbstates[2];
KeyboardState* g_kbstate_current = &kbstates[0];
KeyboardState* g_kbstate_last = &kbstates[1];

void SwapKeyboardStates()
{
	std::swap(g_kbstate_current, g_kbstate_last);
	std::fill_n(g_kbstate_current->keys, sizeof(g_kbstate_current->keys), 0);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	g_kbstate_current->keys[key] = (action != GLFW_RELEASE);
}

void SetupKeyboard(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
}

bool IsKeyPressed(int key)
{
	return g_kbstate_current->keys[key] && !g_kbstate_last->keys[key];
}

bool IsKeyDown(int key)
{
	return g_kbstate_current->keys[key];
}

bool IsKeyReleased(int key)
{
	return !g_kbstate_current->keys[key] && g_kbstate_last->keys[key];
}
