#pragma once
#include "WindowObject.h"
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
	bool _captured = false;
	int _counter = 3;
	float _timer = 0.f;
};

