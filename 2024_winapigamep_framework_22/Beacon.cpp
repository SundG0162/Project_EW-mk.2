#include "pch.h"
#include "Beacon.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "BarUI.h"
#include "Window.h"

Beacon::Beacon(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY, L"Beacon.exe")
{
	_duration = 10.f;
	_timer = _duration;
	_bar = new BarUI({ position.x, position.y - 30 }, { 200,50 });
	GET_SINGLETON(EventManager)->createObject(_bar, LAYER::UI);
	//_bar->getWindow()->openTween();
}

Beacon::~Beacon()
{
}

void Beacon::update()
{
	_timer -= DELTATIME;
	float ratio = 1 - _timer / _duration;
	_bar->setFillAmount(ratio);
}

void Beacon::render(HDC hdc)
{
	
}