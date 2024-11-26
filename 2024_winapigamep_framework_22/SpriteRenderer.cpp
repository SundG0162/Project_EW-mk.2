#include "pch.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Core.h"
#include "Sprite.h"
#include <format>

SpriteRenderer::SpriteRenderer()
	: _sprite(nullptr)
	, _scale{ 1,1 }
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
	Vector2 pos = _owner->getPosition();
	Vector2 size = _sprite->getSize();
	Vector2 scaledSize = _scale * _sprite->getSize();
	TransparentBlt(hDC, pos.x - scaledSize.x / 2, pos.y - scaledSize.y / 2, scaledSize.x, scaledSize.y, _sprite->getSpriteDC(), 0, 0, size.x, size.y, _sprite->getTransparent());
}
