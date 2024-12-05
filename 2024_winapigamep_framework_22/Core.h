#pragma once
#include "Define.h"
#include "Action.h"
class Core
{
	DECLARE_SINGLETON(Core);
public:
	bool init(HWND _hwnd, HINSTANCE hInstance);
	void gameLoop();
	void cleanUp();
private:
	void mainupdate();
	void mainrender();
	void createGDI();
public:
	void onMessageProcess();
	void setStopLoop(bool stop) { _isStopped = stop; }
public:
	const HINSTANCE& getHInstance() const { return _hInstance; }
	const HWND& getHWnd() const { return _hWnd; }
	const HDC& getMainDC() const { return _hDC; }
	const HDC& getBackDC() const { return _hBackDC; }
	const HBRUSH& getBrush(BRUSH_TYPE type)
	{
		return _colorBrushes[(UINT)type];
	}
	const HPEN& getPen(PEN_TYPE _eType)
	{
		return _colorPens[(UINT)_eType];
	}
public:
	Action<> OnMessageProcessEvent;
private:
	bool _isStopped = false;
	HBRUSH _colorBrushes[(UINT)BRUSH_TYPE::END] = {};
	HPEN _colorPens[(UINT)PEN_TYPE::END] = {};
	HINSTANCE _hInstance;
	HWND _hWnd;
	HDC  _hDC;
	HDC  _hBackDC;
	HBITMAP _hBitmap;
};