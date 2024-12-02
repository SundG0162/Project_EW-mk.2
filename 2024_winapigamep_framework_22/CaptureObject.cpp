#include "pch.h"
#include "CaptureObject.h"
#include "Collider.h"
#include "Enemy.h"

CaptureObject::CaptureObject(const Vector2& position, const Vector2& size, const WINDOW_TYPE& type, const wstring& name) : WindowObject(position, size, type, name)
{
	Collider* collider = addComponent<Collider>();
	collider->setSize(size);
	collider->OnCollisionEnterEvent += [this](Collider* other) {this->handleOnCollisionEnter(other); };
	collider->OnCollisionStayEvent += [this](Collider* other) {this->handleOnCollisionStay(other); };
	collider->OnCollisionExitEvent += [this](Collider* other) {this->handleOnCollisionExit(other); };
}

CaptureObject::~CaptureObject()
{
	Collider* collider = getComponent<Collider>();
	collider->OnCollisionEnterEvent -= [this](Collider* other) {this->handleOnCollisionEnter(other); };
	collider->OnCollisionStayEvent -= [this](Collider* other) {this->handleOnCollisionStay(other); };
	collider->OnCollisionExitEvent -= [this](Collider* other) {this->handleOnCollisionExit(other); };
}

void CaptureObject::update()
{
	for (int i = 0; i < _targets.size(); i++)
	{
		Enemy* enemy = _targets[i];
		auto iter = std::find(_temp.begin(), _temp.end(), enemy);
		if (iter == _temp.end())
		{
			_targets.erase(std::find(_targets.begin(), _targets.end(), enemy));
		}
	}
	_temp.clear();
}

void CaptureObject::handleOnCollisionEnter(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
	{
		_targets.push_back(enemy);
		_temp.push_back(enemy);
	}
}

void CaptureObject::handleOnCollisionStay(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
		_temp.push_back(enemy);
}

void CaptureObject::handleOnCollisionExit(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
	{
		auto iter = std::find(_targets.begin(), _targets.end(), enemy);
		if (iter != _targets.end())
		{
			_targets.erase(iter);
		}
	}
}