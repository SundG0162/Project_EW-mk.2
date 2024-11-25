#include "pch.h"
#include "TestObject.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "WindowObject.h"
#include "Window.h"
#include "Utils.h"

TestObject::TestObject() : WindowObject({ 500,400 }, { 300, 600})
{
	Texture* texture = GET_SINGLETON(ResourceManager)->textureFind(L"Test");
	Sprite* sprite = utils::SpriteParser::textureToSprite(texture);
	SpriteRenderer* spriteRenderer = addComponent<SpriteRenderer>();
	spriteRenderer->setSprite(sprite);
}

TestObject::~TestObject()
{
}

void TestObject::update()
{
	WindowObject::update();
}

void TestObject::render(HDC hDC)
{
	utils::Drawer::renderRectColor(hDC, _position, _size.x, _size.y, HOLLOW_BRUSH, RGB(0, 255, 0));
	utils::Drawer::renderRectColor(hDC, _position + _size / 2, _size.x, _size.y, HOLLOW_BRUSH, RGB(0, 255, 0));
	componentRender(hDC);
	WindowObject::render(hDC);
}
