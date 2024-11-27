#include "pch.h"
#include "BaseWindow.h"
#include "Window.h"
#include "Core.h"
#include "TimeManager.h"
#include "WindowManager.h"
#include <functional>

Window::Window(const Vector2& position, const Vector2& size)
	: _hWnd(nullptr)
	, _hDC(nullptr)
	, _position{ position }
	, _size{ size }
{
	WNDCLASS wc = { 0 }; // ����ü�� 0���� �ʱ�ȭ

	wc.lpfnWndProc = Window::wndProc; // ������ ���ν��� �Լ� ����
	wc.hInstance = GET_SINGLETON(Core)->getHInstance(); // �ν��Ͻ� �ڵ� ����
	wc.lpszClassName = L"���ؽ�"; // Ŭ���� �̸� ����
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���� ����

	RegisterClass(&wc);
	Vector2 fixed = GET_LEFTTOPPOS(position, size);

	_hWnd = CreateWindowEx(
		0,                          // Ȯ�� ��Ÿ��
		L"���ؽ�",                  // ������ Ŭ���� �̸�
		L"",            // ������ Ÿ��Ʋ
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,        // ������ ��Ÿ��
		fixed.x, fixed.y,                       // ��ġ (x, y)
		size.x,size.y,                   // ũ�� (width, height)
		NULL,                       // �θ� ������ �ڵ�
		NULL,                       // �޴� �ڵ�
		GET_SINGLETON(Core)->getHInstance(), // �ν��Ͻ� �ڵ�
		NULL                        // �߰� ���ø����̼� ������
	);
	ShowWindow(_hWnd, SW_SHOW);
	GetWindowRect(_hWnd, &_prevRect);
	_hDC = GetDC(_hWnd);
	/*_thread = std::thread(std::bind(&Window::render, this));
	_thread.join();*/
	OnWindowMoveEvent += [this](const Vector2& prev, const Vector2& current) 
		{
			this->handleOnWindowMoveEvent(prev, current);
		};
	GET_SINGLETON(WindowManager)->addWindow(this);

	_leftTopPosition = _position - _size / 2;
}

Window::~Window()
{
}

LRESULT Window::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_PAINT:
		//{
		//    PAINTSTRUCT ps;
		//    HDC hdc = BeginPaint(hWnd, &ps);
		//    
		//    // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		//    EndPaint(hWnd, &ps);
		//}
		//break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Window::openTween(float delayTime)
{
	_delayTime = delayTime;
	_goalSize = _size;
	_size.y = 0;
	_timer = 0.f;
	_isTweenEnd = false;
}

void Window::handleOnWindowMoveEvent(const Vector2& prevPos, const Vector2& curPos)
{
	_position = curPos;
}

void Window::close()
{
}

void Window::moveWindow(const Vector2& pos)
{
	Vector2 leftTop = GET_LEFTTOPPOS(pos, _size);
	SetWindowPos(_hWnd, NULL, leftTop.x, leftTop.y, _size.x, _size.y, SWP_NOZORDER);
	_position = pos;
	_leftTopPosition = _position - _size / 2;
}

void Window::update()
{
	if (!_isTweenEnd)
	{
		_timer += DELTATIME;
		if (_timer < _delayTime)
			return;
		_size.y = std::lerp(0, _goalSize.y, utils::Ease::outQuad(_timer - _delayTime));
		moveWindow(_position);
		if (_timer > _delayTime + 1.f)
			_isTweenEnd = true;
		return;
	}
	RECT currentRect;
	GetWindowRect(_hWnd, &currentRect);
	if (currentRect.top != _prevRect.top || currentRect.bottom != _prevRect.bottom || currentRect.left != _prevRect.left || currentRect.right != _prevRect.right)
	{
		Vector2 prevPosition = { _prevRect.right - _size.x / 2, _prevRect.bottom - _size.y / 2 };
		Vector2 currentPosition = { currentRect.right - _size.x / 2, currentRect.bottom - _size.y / 2 };
		OnWindowMoveEvent.invoke(prevPosition, currentPosition);
	}
	_prevRect = currentRect;
}