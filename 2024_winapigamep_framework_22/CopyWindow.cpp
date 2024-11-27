#include "pch.h"
#include "CopyWindow.h"
#include "Core.h"

CopyWindow::CopyWindow(const Vector2& position, const Vector2& size) : Window(position, size)
{
}

CopyWindow::~CopyWindow()
{
}

void CopyWindow::render(HDC hdc)
{
	BitBlt(_hDC, 0, 0, _size.x, _size.y, hdc, _leftTopPosition.x, _leftTopPosition.y, SRCCOPY);
}