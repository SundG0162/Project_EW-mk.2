#include "pch.h"
#include "BaseWindow.h"
#include "Window.h"
#include "Core.h"
#include "TimeManager.h"
#include "WindowManager.h"
#include "Core.h"

Window::Window(const Vector2& position, const Vector2& size, const wstring& name)
	: _hWnd(nullptr)
	, _hMainDC(nullptr)
	, _position(position)
	, _size(size)
{
	WNDCLASS wc = { 0 }; // ����ü�� 0���� �ʱ�ȭ

	wc.lpfnWndProc = Window::wndProc; // ������ ���ν��� �Լ� ����
	wc.hInstance = GET_SINGLETON(Core)->getHInstance(); // �ν��Ͻ� �ڵ� ����
	wc.lpszClassName = L"���ؽ�"; // Ŭ���� �̸� ����
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ���� ����

	RegisterClass(&wc);

	RECT windowRect = { 0, 0, size.x, size.y };
	AdjustWindowRect(&windowRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);

	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	Vector2 fixedSize = { width,height };

	Vector2 fixedPos = GET_LEFTTOPPOS(position, Vector2(fixedSize.x, fixedSize.y));

	_hWnd = CreateWindowEx(
		0,
		L"���ؽ�",
		name.c_str(),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		fixedPos.x, fixedPos.y,
		fixedSize.x, fixedSize.y,
		NULL,
		NULL,
		GET_SINGLETON(Core)->getHInstance(),
		this
	);
	_leftTopPosition = fixedPos;
	ShowWindow(_hWnd, SW_SHOW);
	_hMainDC = GetDC(_hWnd);
	_size = fixedSize;
	GET_SINGLETON(WindowManager)->addWindow(this);
}

Window::~Window()
{

}


LRESULT CALLBACK Window::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* window = nullptr;

	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<Window*>(create->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
	}
	else
		window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (window)
		return window->handleMessage(hWnd, message, wParam, lParam);
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT Window::handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SYSCOMMAND:
	{
		if (!_moveable)
		{
			switch (wParam & 0xFFF0)
			{
			case SC_MOVE:
			case SC_SIZE:
			case SC_MAXIMIZE:
				return 0;
			}
		}
		else
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_MOVING:
	{
		RECT* rect = (RECT*)lParam;  // �巡�� ���� â�� �� ��ġ
		int posX = rect->left + (rect->right - rect->left) / 2;
		int posY = rect->top + (rect->bottom - rect->top) / 2;
		Vector2 currentPosition = { (float)posX, (float)posY };
		OnWindowMoveEvent.invoke(_position, currentPosition);
		_position = currentPosition;
	}
	break;
	case WM_CLOSE:
	{
		if (_closeable)
		{
			OnWindowCloseEvent.invoke();
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Window::openTween(float delayTime, TWEEN_TYPE type)
{
	_tweenType = type;
	_delayTime = delayTime;
	_goalSize = _size;
	_startSize = { 0,0 };
	switch (type)
	{
	case TWEEN_TYPE::HORIZON:
	{
		_size.x = 0;
	}
	break;
	case TWEEN_TYPE::VERTICAL:
	{
		_size.y = 0;
	}
	break;
	}
	_timer = 0.f;
	_isTweenEnd = false;
}

void Window::closeTween(float delayTime, TWEEN_TYPE type)
{
	setWindowName(L"");
	_tweenType = type;
	_delayTime = delayTime;
	_startSize = _size;
	_goalSize = _size;
	switch (type)
	{
	case TWEEN_TYPE::HORIZON:
	{
		_goalSize.x = 0;
	}
	break;
	case TWEEN_TYPE::VERTICAL:
	{
		_goalSize.y = 0;
	}
	break;
	}
	_timer = 0.f;
	_isTweenEnd = false;
}

void Window::close()
{
	_closeable = true;
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			SendMessage(_hWnd, WM_CLOSE, 0, 0);
			GET_SINGLETON(WindowManager)->removeWindow(this);
			delete this;
		};
	_isDead = true;
}

void Window::moveWindow(const Vector2& pos)
{
	Vector2 leftTop = GET_LEFTTOPPOS(pos, _size);
	SetWindowPos(_hWnd, NULL, leftTop.x, leftTop.y, _size.x, _size.y, SWP_NOZORDER);
	_position = pos;
	_leftTopPosition = leftTop;
}

void Window::setWindowName(const wstring& name)
{
	SetWindowText(_hWnd, name.c_str());
}

void Window::update()
{
	if (!_isTweenEnd)
	{
		_timer += DELTATIME;
		if (_timer < _delayTime)
			return;
		_size.x = std::lerp(_startSize.x, _goalSize.x, utils::Ease::outQuad(_timer - _delayTime));
		_size.y = std::lerp(_startSize.y, _goalSize.y, utils::Ease::outQuad(_timer - _delayTime));
		moveWindow(_position);
		if (_timer > _delayTime + 1.f)
		{
			_isTweenEnd = true;
			OnTweenEndEvent.invoke();
		}
		return;
	}
}