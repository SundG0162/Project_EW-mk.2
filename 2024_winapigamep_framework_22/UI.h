#pragma once
#include "WindowObject.h"
class UI : public WindowObject
{
public:
	UI(const Vector2& position, const Vector2& size, WINDOW_TYPE type);
	virtual ~UI();
};

