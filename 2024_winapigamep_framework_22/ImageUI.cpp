#include "pch.h"
#include "ImageUI.h"
#include "SpriteRenderer.h"

ImageUI::ImageUI(const Vector2& position, const Vector2& size) : UI(position, size)
{
	addComponent<SpriteRenderer>();
}

ImageUI::~ImageUI()
{
}

void ImageUI::update()
{
	WindowObject::update();
}

void ImageUI::render(HDC hdc)
{
	componentRender(hdc);
}

void ImageUI::setSprite(Sprite* sprite)
{
	getComponent<SpriteRenderer>()->setSprite(sprite);
}