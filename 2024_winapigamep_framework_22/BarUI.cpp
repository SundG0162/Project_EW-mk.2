#include "pch.h"
#include "BarUI.h"
#include "GDISelector.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Sprite.h"

BarUI::BarUI(const Vector2& position, const Vector2& size) : UI(position, size, WINDOW_TYPE::NEW)
{
	_fillAmount = 1;
	_isVertical = false;
	_isReverse = false;
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	Sprite* sprite = utils::SpriteParser::textureToSprite(GET_SINGLETON(ResourceManager)->findTexture(L"BarUI"));
	renderer->setSprite(sprite);
	renderer->setScale({ size.x / 32, size.y / 4 });
	_window->setMoveable(true);
}

BarUI::~BarUI()
{
}

void BarUI::update()
{
	if (_fillAmount > 0)
		_fillAmount -= DELTATIME;
}

void BarUI::render(HDC hdc)
{
	float fillAmount = 1 - _fillAmount / 1.f; // 1-0을 0-1로조정
	utils::Drawer::renderRectColor(hdc, _position, _size.x, _size.y, RGB(255, 255, 255), RGB(255, 255, 255));
	Vector fillPos = _position;
	float multiplier = _isReverse ? -1 : 1;
	fillPos.x = _position.x + (_size.x * (1.0f - fillAmount) / 2.0f) * multiplier;
	utils::Drawer::renderRectColor(hdc, fillPos, _size.x * fillAmount, _size.y, RGB(0, 0, 0), RGB(0, 0, 0));
	componentRender(hdc);
}
