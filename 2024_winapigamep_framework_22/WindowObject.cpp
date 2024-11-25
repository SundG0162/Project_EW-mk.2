#include "pch.h"
#include "WindowObject.h"
#include "Window.h"
#include "TimeManager.h"

WindowObject::WindowObject(const Vector2& position, const Vector2& size)
{
	_position = position;
	_size = size;
	_window = new Window(_position, _size);
}

WindowObject::~WindowObject()
{
}

void WindowObject::update()
{
	static Vector2 pos = { 100,400 };
	_window->update();
	_window->moveWindow(pos);
	pos.x += 200 * DELTATIME;
}

void WindowObject::render(HDC hdc)
{
	_window->render(hdc);
}
