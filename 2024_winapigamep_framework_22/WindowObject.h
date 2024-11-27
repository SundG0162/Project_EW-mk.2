#pragma once
#include "Object.h"
class Window;
class WindowObject : public Object
{
public:
	WindowObject(const Vector2& position, const Vector2& size, const WINDOW_TYPE& type);
	virtual ~WindowObject();
public:
	void openTween(float delayTime = 1.f);
	void update() override;
public:
	Window* getWindow() { return _window; }
protected:
	Window* _window;
};

