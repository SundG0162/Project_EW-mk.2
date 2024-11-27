#include "pch.h"
#include "Camera.h"
#include "TimeManager.h"
#include "GDISelector.h"
#include "Window.h"

Camera::Camera(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY)
{
    _window->OnWindowMoveEvent += [this](const Vector2& prev, const Vector2& current) 
        {
            this->handleOnWindowMove(prev, current);
        };
}

Camera::~Camera()
{
    _window->OnWindowMoveEvent -= [this](const Vector2& prev, const Vector2& current)
        {
            this->handleOnWindowMove(prev, current);
        };
}

void Camera::update()
{
	_timer += DELTATIME;
	if (_timer > 1)
	{
		_counter--;
        if (_counter == 0)
        {
            CloseWindow(_window->getHWnd());
            return;
        }
		_timer = 0;
	}
}

void Camera::render(HDC hdc)
{
    HFONT hFont = CreateFont(
        100,
        0,
        0, 0,
        FW_BOLD,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH,
        L"Arial"
    );
    GDISelector gdi = GDISelector(hdc, hFont);
    COLORREF prevColor = SetTextColor(hdc, RGB(255, 255, 255));
	wstring str = std::format(L"{0}", _counter);
	utils::Drawer::renderText(hdc, _position, str);
    SetTextColor(hdc, prevColor);
}

void Camera::handleOnWindowMove(const Vector2& prev, const Vector2& current)
{
    _position = current;
    _window->moveWindow(_position);
}
