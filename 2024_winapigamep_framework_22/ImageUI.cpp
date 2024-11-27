#include "pch.h"
#include "ImageUI.h"
#include "SpriteRenderer.h"

ImageUI::ImageUI(const Vector2& position, const Vector2& size, WINDOW_TYPE type, Sprite* sprite) : UI(position, size, type)
{
	SpriteRenderer* spriteRenderer = addComponent<SpriteRenderer>();
	spriteRenderer->setSprite(sprite);
}

ImageUI::~ImageUI()
{
}

void ImageUI::update()
{
}

void ImageUI::render(HDC hdc)
{
	componentRender(hdc);
}

void ImageUI::setSprite(Sprite* sprite)
{
	getComponent<SpriteRenderer>()->setSprite(sprite);
}