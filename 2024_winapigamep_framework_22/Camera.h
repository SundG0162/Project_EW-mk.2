#pragma once
#include "WindowObject.h"
class BarUI;
class Enemy;
class FadeInOut;
class Collider;
class Camera : public WindowObject
{
public:
	Camera(const Vector2& position, const Vector2& size);
	~Camera();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void handleOnWindowMove(const Vector2& prev, const Vector2& current);
	void handleOnCollisionEnter(Collider* other);
	void handleOnCollisionExit(Collider* other);
public:
	vector<Enemy*> _targets;
	FadeInOut* _fadeOut;
	BarUI* _bar;
	int _counter;
	int _maxCount;
	int _attackDamage = 3;
	float _timer = 0.f;
};