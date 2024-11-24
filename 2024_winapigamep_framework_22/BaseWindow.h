#pragma once
class BaseWindow
{
public:
	BaseWindow();
	~BaseWindow();
public:
	int run(HINSTANCE hInst, LPWSTR _lpCmdline, int nCmdShow);
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	ATOM myRegisterClass(); // 1
	void createWindow();   // 2
	void showWindow(int nCmdShow); // 3
	void updateWindow(); // 4
	int  messageLoop(); // 5
private:
	HINSTANCE _hInstance;
	HWND	  _hWnd;
};

