#include "pch.h"
#include "BaseWindow.h"
#include "Window.h"
#include "Core.h"
#include <functional>

Window::Window(const Vector2& position, const Vector2& size)
	: _thread{}
	, _hWnd(nullptr)
	, _hMainDC(nullptr)
	, _hDC(nullptr)
	, _position{ position }
	, _size{ size }
{
	WNDCLASS wc = { 0 }; // ����ü�� 0���� �ʱ�ȭ

	wc.lpfnWndProc = BaseWindow::wndProc; // ������ ���ν��� �Լ� ����
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
	_hMainDC = GET_SINGLETON(Core)->getMainDC();
	_hDC = GetDC(_hWnd);
	/*_thread = std::thread(std::bind(&Window::render, this));
	_thread.join();*/
	OnWindowMoveEvent += std::bind(&Window::handleOnWindowMoveEvent, this, std::placeholders::_1, std::placeholders::_2);
}

Window::~Window()
{
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
}

void Window::update()
{
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

void Window::render(HDC hdc)
{
	BitBlt(_hDC, 0, 0, _size.x, _size.y, hdc, _position.x - _size.x / 2, _position.y - _size.y / 2, SRCCOPY);
}