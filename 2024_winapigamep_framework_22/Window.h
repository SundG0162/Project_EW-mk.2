#pragma once
#include <thread>
#include "Action.h"
class Window
{
public:
	Window(const Vector2& position, const Vector2& size);
	virtual ~Window();
public:
	void update();
	void render(HDC hdc);
public:
	void handleOnWindowMoveEvent(const Vector2& prevPos, const Vector2& curPos);
	void close();
	void moveWindow(const Vector2& pos);
public:
	void setPosition(const Vector2& position) { _position = position; }
	const Vector2& getPosition() { return _position; }
	void setSize(const Vector2& size) { _size = size; }
	const Vector2& getSize() { return _size; }
	const HWND& getHWnd() { return _hWnd; }
public:
	Action<const Vector2&, const Vector2&> OnWindowMoveEvent;
protected:
	std::thread _thread;
	HWND _hWnd;
	HDC _hMainDC;
	HDC _hDC;
	Vector2 _position;
	Vector2 _size;

private:
	bool _isInvoked = false;
	RECT _prevRect;
};