#pragma once

#include <GLFW/glfw3.h>

struct KeyboardState
{
	bool keys[GLFW_KEY_LAST + 1];
};

void SetupKeyboard(GLFWwindow* window);
void swap_kbstates();
bool is_key_pressed(int key);
bool is_key_down(int key);
bool is_key_released(int key);

