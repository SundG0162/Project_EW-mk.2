#include "pch.h"
#include "CopyWindow.h"
#include "Core.h"

CopyWindow::CopyWindow(const Vector2& position, const Vector2& size) : Window(position, size)
{
	_hBackDC = GET_SINGLETON(Core)->getBackDC();
}

CopyWindow::~CopyWindow()
{
}

void CopyWindow::render()
{
	BitBlt(_hDC, 0, 0, _size.x, _size.y, _hBackDC, 0, 0, SRCCOPY);
}