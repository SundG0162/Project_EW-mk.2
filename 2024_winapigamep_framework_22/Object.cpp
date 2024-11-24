#include "pch.h"
#include "Object.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Component.h"
Object::Object()
	: _position{}
	, _size{}
	, _isDead(false)
{
}

Object::~Object()
{
	for (Component* com : _components)
	{
		if (com != nullptr)
			delete com;
	}
	_components.clear();
}

void Object::lateUpdate()
{
	for (Component* com : _components)
	{
		if (com)
		{
			com->lateUpdate();
		}
	}
}

void Object::componentrender(HDC hDC)
{
	for (Component* com : _components)
	{
		if (com)
		{
			com->render(hDC);
		}
	}
}
