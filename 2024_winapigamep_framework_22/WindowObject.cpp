#include "pch.h"
#include "WindowObject.h"
#include "Window.h"
#include "NewWindow.h"
#include "CopyWindow.h"
#include "TimeManager.h"

WindowObject::WindowObject(const Vector2& position, const Vector2& size, const WINDOW_TYPE& type)
{
	if (type == WINDOW_TYPE::COPY)
		_position = position;
	_size = size;
	if (type == WINDOW_TYPE::NEW)
		_position = _size / 2;
	_type = type;
	switch (type)
	{
	case WINDOW_TYPE::NEW:
	{
		_window = new NewWindow(position, size);
	}
	break;
	case WINDOW_TYPE::COPY:
	{
		_window = new CopyWindow(position, size);
	}
	break;
	}
}

WindowObject::~WindowObject()
{
	_window->close();
	SAFE_DELETE(_window);
}

void WindowObject::openTween(float delayTime)
{
	_window->openTween(delayTime);
}