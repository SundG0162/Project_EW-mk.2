#include "pch.h"
#include "TestObject.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Utils.h"

TestObject::TestObject() : Object()
{
	_position = Vector2(300, 300);
	_size = Vector2(2, 1);
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
}

void TestObject::render(HDC hDC)
{
	componentRender(hDC);
}
