#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"
#include "Core.h"
BaseWindow::BaseWindow()
	: _hWnd(nullptr)
	, _hInstance(nullptr)
{
}

BaseWindow::~BaseWindow()
{
}

int BaseWindow::run(HINSTANCE hInst, LPWSTR lpCmdline, int nCmdShow)
{
	this->_hInstance = hInst;
	this->myRegisterClass();
	this->createWindow();
	this->showWindow(nCmdShow);
	this->updateWindow();
	if (!GET_SINGLETON(Core)->init(_hWnd, _hInstance))
		MessageBox(_hWnd, L"Core init Error", L"Error", MB_OK);
	return this->messageLoop();
}

LRESULT BaseWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM BaseWindow::myRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BaseWindow::wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_MY2024WINAPIGAMEPFRAMEWORK22));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"2-2 Gamep";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

void BaseWindow::createWindow()
{
	int ResolutionX = GetSystemMetrics(SM_CXSCREEN);
	int ResolutionY = GetSystemMetrics(SM_CYSCREEN);

	int Winposx = 0;
	int Winposy = 0;

	_hWnd = CreateWindowW(
		L"2-2 Gamep", // ������ Ŭ���� �ĺ���
		L"�ؿ��� ������",   // ����
		WS_OVERLAPPEDWINDOW, // ������ � ��Ÿ�Ϸ� ������ΰ�
		Winposx,  // �� ��� ��ġ�� LEFT
		Winposy,             // �� ��� ��ġ�� TOP
		SCREEN_WIDTH,             // �� �ػ�X
		SCREEN_HEIGHT,             // �� �ػ�Y
		nullptr,       // �θ� ������ ��¼���� ����
		nullptr,       // �޴�������
		_hInstance,     // �� ���α׷� �ν��Ͻ� �� 
		nullptr);      // �ڽ� ������ ���õȰ� ����

	// ������ ������ ����(Ÿ��Ʋ, �޴� ������� �ʵ���)
	RECT rt = { 0 , 0,
				 0 + SCREEN_WIDTH,
				 0 + SCREEN_HEIGHT };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	MoveWindow(_hWnd, Winposx, Winposy,
		rt.right - rt.left, rt.bottom - rt.top, false);
}

void BaseWindow::showWindow(int nCmdShow)
{
	// global namespace
	::ShowWindow(_hWnd, nCmdShow);
}

void BaseWindow::updateWindow()
{
	::UpdateWindow(_hWnd); // WM_PAINT
}

int BaseWindow::messageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg)); // 0 �ʱ�ȭ
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ���� �ڵ�
			GET_SINGLETON(Core)->gameLoop();
		}
	}
	GET_SINGLETON(Core)->cleanUp();
	return (int)msg.wParam;
}
