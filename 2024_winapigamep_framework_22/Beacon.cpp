#include "pch.h"
#include "Beacon.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "BarUI.h"
#include "Window.h"
#include "WindowUI.h"

Beacon::Beacon(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY, L"Beacon.exe")
{
	_duration = 10.f;
	_timer = _duration;
	_bar = new WindowUI({ position.x - 30, position.y - size.y / 3}, { 320,40 }, WINDOW_TYPE::NEW, L"Ember.exe");
	BarUI* bar = new BarUI({ _bar->getSize().x / 2, _bar->getSize().y / 2 }, { 320,40 });
	_bar->getWindow()->setMoveable(true);
	_bar->getWindow()->setCloseable(true);
	_bar->setUI(bar);
	GET_SINGLETON(EventManager)->createObject(_bar, LAYER::UI);
}

Beacon::~Beacon()
{
}

void Beacon::update()
{
	_timer -= DELTATIME;
	float ratio = _timer / _duration;
	dynamic_cast<BarUI*>(_bar->getUI())->setFillAmount(ratio);
}

void Beacon::render(HDC hdc)
{
}
