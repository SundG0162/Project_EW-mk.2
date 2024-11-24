#include "pch.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Sprite.h"

SpriteRenderer::SpriteRenderer()
	:_sprite(nullptr)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::lateUpdate()
{
}

void SpriteRenderer::render(HDC hDC)
{
	if (_sprite == nullptr) return;
	Vector2 pos = _owner->getPosition();
	Vector2 size = _sprite->getSize();
	TransparentBlt(hDC, pos.x - size.x / 2, pos.y - size.y / 2, size.x, size.y, _sprite->getSpriteDC(), 0, 0, size.x, size.y, _sprite->getTransparent());
}
