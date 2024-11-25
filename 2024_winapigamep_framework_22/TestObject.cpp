#include "pch.h"
#include "TestObject.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "WindowObject.h"
#include "Window.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"

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
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		_window->openTween();
	}
	if (GET_KEY(KEY_TYPE::D))
	{
		_position.x += 300 * DELTATIME;
	}
	if (GET_KEY(KEY_TYPE::A))
	{
		_position.x -= 300 * DELTATIME;
	}
	WindowObject::update();
}

void TestObject::render(HDC hDC)
{
	componentRender(hDC);
	WindowObject::render(hDC);
}
