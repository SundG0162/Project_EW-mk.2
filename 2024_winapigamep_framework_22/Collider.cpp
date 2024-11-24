#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "GDISelector.h"
UINT Collider::_nextID = 0;
Collider::Collider()
	: _size(30.f, 30.f)
	, _position(0.f, 0.f)
	, _offset(0.f, 0.f)
{
}

Collider::~Collider()
{
}

void Collider::lateUpdate()
{
	const Object* pOwner = getOwner();
	Vector2 vPos = pOwner->getPosition();
	_position = vPos + _offset;
}

void Collider::render(HDC _hdc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (_showDebug)
		ePen = PEN_TYPE::RED;
	GDISelector pen(_hdc, ePen);
	GDISelector brush(_hdc, BRUSH_TYPE::HOLLOW);
	RECT_render(_hdc, _position.x, _position.y,
		_size.x, _size.y);
}

void Collider::enterCollision(Collider* _other)
{
	_showDebug = true;
	//cout << "Enter" << endl;
	//GetOwner()->EnterCollision(_other);
}

void Collider::stayCollision(Collider* _other)
{
	//GetOwner()->StayCollision(_other);
}

void Collider::exitCollision(Collider* _other)
{
	_showDebug = false;
	//cout << "Exit" << endl;
	//GetOwner()->ExitCollision(_other);
}
