#include "pch.h"
#include "NewWindow.h"
#include "Core.h"

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

void NewWindow::closeWindow()
{
	DeleteObject(_hBitmap);
	DeleteDC(_hBackDC);
	ReleaseDC(_hWnd,_hMainDC);
	Window::closeWindow();
}

void NewWindow::openWindow()
{
	_isClosed = false;
	OnWindowOpenEvent.invoke();
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
			WNDCLASS wc = { 0 }; // ����ü�� 0���� �ʱ�ȭ

			wc.lpfnWndProc = Window::wndProc; // ������ ���ν��� �Լ� ����
			wc.hInstance = GET_SINGLETON(Core)->getHInstance(); // �ν��Ͻ� �ڵ� ����
			wc.lpszClassName = L"���ؽ�"; // Ŭ���� �̸� ����
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���� ����

			RegisterClass(&wc);

			Vector2 fixedPos = GET_LEFTTOPPOS(_position, _size);

			_hWnd = CreateWindowEx(
				0,
				L"���ؽ�",
				_name.c_str(),
				WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
				fixedPos.x, fixedPos.y,
				_size.x, _size.y,
				NULL,
				NULL,
				GET_SINGLETON(Core)->getHInstance(),
				this
			);
			_leftTopPosition = fixedPos;
			ShowWindow(_hWnd, SW_SHOW);
			_hMainDC = GetDC(_hWnd);
			_hBackDC = CreateCompatibleDC(_hMainDC);
			_hBitmap = CreateCompatibleBitmap(_hMainDC, _size.x, _size.y);
			SelectObject(_hBackDC, _hBitmap);
		};
}
