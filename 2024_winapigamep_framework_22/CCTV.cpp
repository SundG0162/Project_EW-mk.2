#include "pch.h"
#include "CCTV.h"
#include "Window.h"
#include "Collider.h"
#include "Enemy.h"
#include "TimeManager.h"

CCTV::CCTV(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY, L"CCTV.exe")
{
	Collider* collider = addComponent<Collider>();
	collider->setSize(size);
	collider->OnCollisionEnterEvent += [this](Collider* other) {this->handleOnCollisionEnter(other); };
	collider->OnCollisionExitEvent += [this](Collider* other) {this->handleOnCollisionExit(other); };
	collider->setFollowing(false);
	SetActiveWindow(_window->getHWnd());
}

CCTV::~CCTV()
{
	Collider* collider = getComponent<Collider>();
	collider->OnCollisionEnterEvent -= [this](Collider* other) {this->handleOnCollisionEnter(other); };
	collider->OnCollisionExitEvent -= [this](Collider* other) {this->handleOnCollisionExit(other); };
}

void CCTV::update()
{
	Collider* collider = getComponent<Collider>();
	RECT rect = {0,0,_size.x,_size.y};
	GetWindowRect(_window->getHWnd(), &rect);
	collider->setPosition(utils::CoordinateSync::nonClientToClient(rect, _position));
	tryAttack();
}

void CCTV::render(HDC hdc)
{
	componentRender(hdc);
}

void CCTV::handleOnCollisionEnter(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
		_targets.push_back(enemy);
}

void CCTV::handleOnCollisionExit(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
	{
		auto iter = find(_targets.begin(), _targets.end(), enemy);
		if (iter != _targets.end())
		{
			_targets.erase(iter);
		}
	}
}

void CCTV::localMove(const Vector2& move)
{
	_position += move;
	_window->moveWindow(_position);
}

void CCTV::tryAttack()
{
	_attackTimer += DELTATIME;
	if (_attackTimer >= _attackTime)
	{
		_attackTimer = 0.f;
		attack();
	}
}

void CCTV::attack()
{
	vector<Enemy*> deadVec;
	for (Enemy* enemy : _targets)
	{
		enemy->GetDamage(_attackDamage);
		if (enemy->isDead())
			deadVec.push_back(enemy);
	}
	for (Enemy* enemy : deadVec)
	{
		auto iter = std::find(_targets.begin(), _targets.end(), enemy);
		if (iter != _targets.end())
			_targets.erase(iter);
	}
}
