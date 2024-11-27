#include "pch.h"
#include "WindowManager.h"
#include "Window.h"

WindowManager::~WindowManager()
{
}

void WindowManager::update()
{
	for (Window* window : _windows)
		if (window)
			window->update();
}

void WindowManager::render()
{
	for (Window* window : _windows)
		if (window)
			window->render();
}
