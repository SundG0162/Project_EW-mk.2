#pragma once
#include "Object.h"
class Window;
class WindowObject : public Object
{
public:
	WindowObject(const Vector2& position, const Vector2& size);
	virtual ~WindowObject();
public:
	void openTween(float delayTime = 1.f);
	void update() override;
protected:
	Window* _window;
};

