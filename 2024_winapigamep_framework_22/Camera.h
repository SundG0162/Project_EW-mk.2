#pragma once
#include "WindowObject.h"
class BarUI;
class FadeInOut;
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
public:
	FadeInOut* _fadeOut;
	BarUI* _bar;
	int _counter;
	int _maxCount;
	float _timer = 0.f;
};

