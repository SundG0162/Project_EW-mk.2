#pragma once
#include "CaptureObject.h"
#include "PlayerDevice.h"
class WindowUI;
class Beacon : public CaptureObject, public PlayerDevice
{
public:
	Beacon(const Vector2& position, const Vector2& size);
	~Beacon();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void setDuration(float duration) { _duration = duration; }
private:
	WindowUI* _bar;
	float _duration;
	float _timer;
};