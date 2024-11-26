#pragma once
#include "UI.h"
class Sprite;
class ImageUI : public UI
{
public:
	ImageUI(const Vector2& position, const Vector2& size, Sprite* sprite);
	~ImageUI();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void setSprite(Sprite* sprite);
};

