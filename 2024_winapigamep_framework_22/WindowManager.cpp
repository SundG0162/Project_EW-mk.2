#include "pch.h"
#include "WindowManager.h"
#include "Core.h"
#include "Window.h"
#include "CopyWindow.h"
#include "NewWindow.h"

WindowManager::~WindowManager()
{
}

void WindowManager::update()
{
	for (Window* window : _windows)
	{
   		if (window->isDead())
		{
			_windows.erase(std::find(_windows.begin(), _windows.end(), window));
		}
		window->update();
	}
}

void WindowManager::render()
{
	for (Window* window : _windows)
	{
		if (window == nullptr) continue;
		if (window->isDead()) continue;
		CopyWindow* copyWindow = dynamic_cast<CopyWindow*>(window);
		if (copyWindow)
		{
			copyWindow->render(GET_SINGLETON(Core)->getBackDC());
			continue;
		}
		NewWindow* newWindow = dynamic_cast<NewWindow*>(window);
		if (newWindow)
		{
			newWindow->render(newWindow->getBackDC());
			continue;
		}
	}
}