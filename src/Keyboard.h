#pragma once

#include <GLFW/glfw3.h>

struct KeyboardState
{
	bool keys[GLFW_KEY_LAST + 1];
};

void SetupKeyboard(GLFWwindow* window);
void SwapKeyboardStates();
bool IsKeyPressed(int key);
bool IsKeyDown(int key);
bool IsKeyReleased(int key);

