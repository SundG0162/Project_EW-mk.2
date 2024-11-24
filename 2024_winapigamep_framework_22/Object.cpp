#include "pch.h"
#include "Object.h"
#include "Component.h"


Object::Object()
	: _position{}
	, _size{}
	, _isDead(false)
{
}

Object::~Object()
{
}

void Object::lateUpdate()
{
	componentUpdate();
}

void Object::componentUpdate()
{
	for (Component* compo : _components)
	{
		if (compo)
		{
			compo->lateUpdate();
		}
	}
}

void Object::componentRender(HDC hdc)
{
	for (Component* compo : _components)
	{
		if (compo)
		{
			compo->render(hdc);
		}
	}
}
