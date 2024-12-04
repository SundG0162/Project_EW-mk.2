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
	void setup(const Vector2& position);
	void setDuration(float duration) { _duration = duration; }
private:
	Vector2 _startPos;
	Vector2 _goalPos;
	bool _settingUp;
	WindowUI* _bar;
	float _duration;
	float _timer;
};