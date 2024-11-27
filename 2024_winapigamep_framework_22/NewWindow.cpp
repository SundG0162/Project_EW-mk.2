#include "pch.h"
#include "NewWindow.h"

NewWindow::NewWindow(const Vector2& position, const Vector2& size) : Window(position, size)
{
	_hBackDC = CreateCompatibleDC(_hDC);
	_hBitmap = CreateCompatibleBitmap(_hDC, _size.x, _size.y);
	SelectObject(_hBackDC, _hBitmap);
}

NewWindow::~NewWindow()
{
}

void NewWindow::render()
{
	BitBlt(_hDC, 0, 0, _size.x, _size.y, _hBackDC, 0, 0, SRCCOPY);
}