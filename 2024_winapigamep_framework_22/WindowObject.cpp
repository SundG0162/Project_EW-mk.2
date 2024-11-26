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

void WindowObject::openTween()
{
	_window->openTween();
}

void WindowObject::update()
{
	_window->moveWindow(_position);
}