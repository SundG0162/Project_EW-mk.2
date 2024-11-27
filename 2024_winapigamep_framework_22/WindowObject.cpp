#include "pch.h"
#include "WindowObject.h"
#include "Window.h"
#include "NewWindow.h"
#include "CopyWindow.h"
#include "TimeManager.h"

WindowObject::WindowObject(const Vector2& position, const Vector2& size, const WINDOW_TYPE& type)
{
	_position = position;
	_size = size;
	switch (type)
	{
	case WINDOW_TYPE::NEW:
	{
		_window = new NewWindow(_position, _size);
	}
	break;
	case WINDOW_TYPE::COPY:
	{
		_window = new CopyWindow(_position, _size);
	}
	break;
	}
}

WindowObject::~WindowObject()
{
}

void WindowObject::openTween(float delayTime)
{
	_window->openTween(delayTime);
}

void WindowObject::update()
{
	_window->moveWindow(_position);
}