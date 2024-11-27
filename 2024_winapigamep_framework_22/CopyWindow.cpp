#include "pch.h"
#include "CopyWindow.h"
#include "Core.h"

CopyWindow::CopyWindow(const Vector2& position, const Vector2& size) : Window(position, size)
{
	_hBackDC = nullptr;
}

CopyWindow::~CopyWindow()
{
}

void CopyWindow::render()
{
	_hBackDC = GET_SINGLETON(Core)->getBackDC();
	BitBlt(_hDC, 0, 0, _size.x, _size.y, _hBackDC, _position.x - _size.x / 2, _position.y - _size.y / 2, SRCCOPY);
}