#include "pch.h"
#include "WindowUI.h"
#include "UI.h"
#include "NewWindow.h"
#include "BarUI.h"

WindowUI::WindowUI(const Vector2& position, const Vector2& size, WINDOW_TYPE type, const wstring& name) : WindowObject(position, size, type, name)
{
	_ui = nullptr;
}

WindowUI::~WindowUI()
{
}

void WindowUI::update()
{
	_ui->update();
}

void WindowUI::render(HDC hdc)
{
	_ui->render(hdc);
}
