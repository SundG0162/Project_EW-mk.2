#include "pch.h"
#include "NewWindow.h"

NewWindow::NewWindow(const Vector2& position, const Vector2& size) : Window(position, size)
{
}

NewWindow::~NewWindow()
{
}

void NewWindow::render(HDC hdc)
{
	BitBlt(_hMainDC, 0, 0, _size.x, _size.y, hdc, 0, 0, SRCCOPY);
}