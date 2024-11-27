#pragma once
#include "WindowObject.h"
class CCTV : public WindowObject
{
public:
	CCTV(const Vector2& position, const Vector2& size);
	~CCTV();
public:
	void update() override;
	void render(HDC hdc) override;
};