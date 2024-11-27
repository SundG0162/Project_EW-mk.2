#pragma once
#include "Window.h"
class NewWindow : public Window
{
public:
	NewWindow(const Vector2& position, const Vector2& size);
	~NewWindow();
public:
	void render() override;
public:
	const HDC& getBackDC() { return _hBackDC; }
private:
	HDC _hBackDC;
	HBITMAP _hBitmap;
};

