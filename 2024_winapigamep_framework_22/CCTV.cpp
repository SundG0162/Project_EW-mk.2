#include "pch.h"
#include "CCTV.h"
#include "Window.h"
#include "Collider.h"

CCTV::CCTV(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY)
{
	Collider* collider = addComponent<Collider>();
	collider->setSize(size);
	collider->OnCollisionEnterEvent += [this](Collider* other) {this->handleOnCollisionEnter(other); };
	collider->OnCollisionExitEvent += [this](Collider* other) {this->handleOnCollisionExit(other); };
}

CCTV::~CCTV()
{
	Collider* collider = getComponent<Collider>();
	collider->OnCollisionEnterEvent -= [this](Collider* other) {this->handleOnCollisionEnter(other); };
	collider->OnCollisionExitEvent -= [this](Collider* other) {this->handleOnCollisionExit(other); };
}

void CCTV::update()
{
}

void CCTV::render(HDC hdc)
{
}

void CCTV::handleOnCollisionEnter(Collider* other)
{
	_targets.push_back(other->getOwner());
}

void CCTV::handleOnCollisionExit(Collider* other)
{
	auto iter = find(_targets.begin(), _targets.end(), other->getOwner());
	if (iter != _targets.end())
	{
		_targets.erase(iter);
	}
}

void CCTV::localMove(const Vector2& move)
{
	_position += move;
	_window->moveWindow(_position);
}
