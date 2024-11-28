#include "pch.h"
#include "Camera.h"
#include "TimeManager.h"
#include "GDISelector.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "InputManager.h"

Camera::Camera(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY)
{
    _window->OnWindowMoveEvent += [this](const Vector2& prev, const Vector2& current) 
        {
            this->handleOnWindowMove(prev, current);
        };
    SpriteRenderer* renderer = addComponent<SpriteRenderer>();
    Sprite* sprite = utils::SpriteParser::textureToSprite(GET_SINGLETON(ResourceManager)->textureFind(L"Camera"));
    renderer->setSprite(sprite);
    renderer->setScale({ 5, 5 });
    _window->setCloseable(false);
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
    if (_captured)
    {
        if (_timer > 1)
        {
            PatBlt(GetDC(_window->getHWnd()), 0, 0, _size.x, _size.y, WHITENESS);
            GET_SINGLETON(EventManager)->deleteObject(this);
        }
        return;
    }
	if (_timer > 1)
	{
        _timer = 0;
		_counter--;
        if (_counter == 0)
        {
            _captured = true;
            return;
        }
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
	utils::Drawer::renderText(hdc, GET_LEFTTOPPOS(_position, _size), str);
    SetTextColor(hdc, prevColor);
    componentRender(hdc);
}

void Camera::handleOnWindowMove(const Vector2& prev, const Vector2& current)
{
    _position = current;
    _window->moveWindow(_position);
}
