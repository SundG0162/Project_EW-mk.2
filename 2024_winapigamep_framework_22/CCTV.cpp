#include "pch.h"
#include "CCTV.h"
#include "Window.h"

CCTV::CCTV(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY)
{
}

CCTV::~CCTV()
{
}

void CCTV::update()
{
}

void CCTV::render(HDC hdc)
{
}

void CCTV::localMove(const Vector2& move)
{
	_position += move;
	_window->moveWindow(_position);
}
