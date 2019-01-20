#include "Keyboard.h"
#include <algorithm>
#include <utility>

KeyboardState kbstates[2];

KeyboardState* kbstate_curr = &kbstates[0];
KeyboardState* kbstate_last = &kbstates[1];

void swap_kbstates()
{
	std::swap(kbstate_curr, kbstate_last);
	std::fill_n(kbstate_curr->keys, sizeof(kbstate_curr->keys), 0);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	kbstate_curr->keys[key] = (action == GLFW_PRESS);
}

void SetupKeyboard(GLFWwindow* window)
{
	glfwSetKeyCallback(window, key_callback);
}

bool is_key_pressed(int key)
{
	return kbstate_curr->keys[key] && !kbstate_last->keys[key];
}

bool is_key_down(int key)
{
	return kbstate_curr->keys[key];
}

bool is_key_released(int key)
{
	return !kbstate_curr->keys[key] && kbstate_last->keys[key];
}
