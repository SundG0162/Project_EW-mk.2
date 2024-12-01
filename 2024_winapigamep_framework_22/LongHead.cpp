#include "pch.h"
#include "LongHead.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"

LongHead::LongHead()
{
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	GET_SINGLETON(ResourceManager)->loadTexture(L"LongHead", L"Texture\\LongHead.bmp");
	sp->setSprite(utils::SpriteParser::textureToSprite(
		GET_SINGLETON(ResourceManager)->findTexture(L"LongHead")));
	Collider* collider = addComponent<Collider>();
	cout << "setted";
	//collider->enterCollision
}

LongHead::LongHead(const Vector2& pos, Object* target)
{
	setPos(pos);
	SetTarget(target);
	SpriteRenderer* sp = addComponent<SpriteRenderer>();
	GET_SINGLETON(ResourceManager)->loadTexture(L"LongHead", L"Texture\\LongHead.bmp");
	sp->setSprite(utils::SpriteParser::textureToSprite(
		GET_SINGLETON(ResourceManager)->findTexture(L"LongHead")));
	Collider* collider = addComponent<Collider>();
}

LongHead::~LongHead()
{
}

void LongHead::update()
{
	Enemy::update();
}

void LongHead::render(HDC hdc)
{
	Enemy::render(hdc);
}
