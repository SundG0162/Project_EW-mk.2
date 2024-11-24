#pragma once
#include "Define.h"
class Core
{
	DECLARE_SINGLETON(Core);
public:
	bool init(HWND _hwnd);
	void gameLoop();
	void cleanUp();
private:
	void mainupdate();
	void mainrender();
	void createGDI();
public:
	const HWND& getHWnd() const { return _hWnd; }
	const HDC& getMainDC() const { return hDC; }
	const HBRUSH& getBrush(BRUSH_TYPE type)
	{
		return _colorBrushes[(UINT)type];
	}
	const HPEN& getPen(PEN_TYPE _eType)
	{
		return _colorPens[(UINT)_eType];
	}

private:
	HBRUSH _colorBrushes[(UINT)BRUSH_TYPE::END] = {};
	HPEN _colorPens[(UINT)PEN_TYPE::END] = {};

	HWND _hWnd;
	HDC  hDC;
	HDC  _hBackDC;
	HBITMAP _hBitmap;
};