#include "pch.h"
#include "CCTV.h"
#include "Window.h"
#include "Collider.h"
#include "Enemy.h"
#include "Player.h"
#include "TimeManager.h"
#include "StatComponent.h"
#include "Stat.h"

CCTV::CCTV(const Vector2& position, const Vector2& size) : CaptureObject(position, size, WINDOW_TYPE::COPY, L"CCTV.exe")
{
	_collider->setFollowing(false);
}

CCTV::~CCTV()
{
}

void CCTV::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void CCTV::update()
{
	CaptureObject::update();
	RECT rect = {0,0,_size.x,_size.y};
	GetWindowRect(_window->getHWnd(), &rect);
	_collider->setPosition(utils::CoordinateSync::nonClientToClient(rect, _position));
	tryAttack();
}

void CCTV::render(HDC hdc)
{
	componentRender(hdc);
}

void CCTV::localMove(const Vector2& move)
{
	_position += move;
	_window->moveWindow(_position);
}

void CCTV::tryAttack()
{
	_attackTimer += DELTATIME;
	if (_attackTimer >= _statComponent->getStat(L"AttackSpeed")->getValue())
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
		enemy->GetDamage(_statComponent->getStat(L"Damage")->getValue());
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
