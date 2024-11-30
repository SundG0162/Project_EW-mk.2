#include "pch.h"
#include "ImageUI.h"
#include "SpriteRenderer.h"

ImageUI::ImageUI(const Vector2& position, const Vector2& size, WINDOW_TYPE type, Sprite* sprite, const wstring& name) : UI(position, size, type, name)
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