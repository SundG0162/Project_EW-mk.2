#pragma once
#include "CaptureObject.h"
class Collider;
class Enemy;
class CCTV : public CaptureObject
{
public:
	CCTV(const Vector2& position, const Vector2& size);
	~CCTV();
public:
	void init() override;
	void update() override;
	void render(HDC hdc) override;
public:
	void localMove(const Vector2& move);
	void tryAttack();
	void attack();
private:
	int _attackDamage = 1;
	float _attackTimer = 0.f;
	float _attackTime = 1.5f;
};