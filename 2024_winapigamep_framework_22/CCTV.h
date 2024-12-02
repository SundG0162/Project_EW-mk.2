#pragma once
#include "WindowObject.h"
class Collider;
class Enemy;
class CCTV : public WindowObject
{
public:
	CCTV(const Vector2& position, const Vector2& size);
	~CCTV();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void handleOnCollisionEnter(Collider* other);
	void handleOnCollisionExit(Collider* other);
public:
	void localMove(const Vector2& move);
	void tryAttack();
	void attack();
private:
	vector<Enemy*> _targets;

	int _attackDamage = 1;
	float _attackTimer = 0.f;
	float _attackTime = 1.5f;
};