#include "pch.h"
#include "NewWindow.h"

NewWindow::NewWindow(const Vector2& position, const Vector2& size, const wstring& name) : Window(position, size, name)
{
	_hBackDC = CreateCompatibleDC(_hMainDC);
	_hBitmap = CreateCompatibleBitmap(_hMainDC, size.x, size.y);
	SelectObject(_hBackDC, _hBitmap);
}

NewWindow::~NewWindow()
{
}

void NewWindow::render(HDC hdc)
{
	BitBlt(_hMainDC, 0, 0, _size.x, _size.y, hdc, 0, 0, SRCCOPY);
}