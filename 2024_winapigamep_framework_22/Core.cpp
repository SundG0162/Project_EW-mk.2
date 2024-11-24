#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
bool Core::init(HWND _hwnd)
{
	// 변수 초기화
	_hWnd = _hwnd;
	_hDC = ::GetDC(_hWnd);
	_hBackDC = 0;
	_hBitmap = 0;

	// 더블 버퍼링
	// 1. 생성(세팅)
	_hBitmap = ::CreateCompatibleBitmap(_hDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	_hBackDC =::CreateCompatibleDC(_hDC);

	// 2. 연결
	::SelectObject(_hBackDC,_hBitmap);
	
	createGDI();
	// === Manager init === 
	GET_SINGLETON(TimeManager)->init();
	GET_SINGLETON(InputManager)->init();
	GET_SINGLETON(ResourceManager)->init();
	GET_SINGLETON(SceneManager)->init();

	//m_obj.SetPos(Vec2(SCREEN_WIDTH / 2
	//				,SCREEN_HEIGHT/ 2));
	//m_obj.SetSize(Vec2(100, 100));
	return true;
}
void Core::cleanUp()
{
	// 생성한순서 반대로 삭제
	::DeleteDC(_hBackDC);	//createdc한거
	::DeleteObject(_hBitmap); // createbitmap 한거
	::ReleaseDC(_hWnd, _hDC);
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(_colorPens[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		// Hollow 제외하고
		DeleteObject(_colorBrushes[i]);
	}

	GET_SINGLETON(ResourceManager)->release();
}

void Core::gameLoop()
{
	//static int callcount = 0;
	//++callcount;
	//static int prev = GetTickCount64();
	//int cur = GetTickCount64();
	//if (cur - prev > 1000)
	//{
	//	prev = cur;
	//	callcount = 0;
	//}
	mainupdate();
	mainrender();
	GET_SINGLETON(EventManager)->update();
}



void Core::mainupdate()
{
	// === Manager update === 
	GET_SINGLETON(TimeManager)->update();
	GET_SINGLETON(InputManager)->update();
	GET_SINGLETON(SceneManager)->update();
	GET_SINGLETON(CollisionManager)->update();

}

void Core::mainrender()
{
	// 1. clear
	::PatBlt(_hBackDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);
	// 2. render
	GET_SINGLETON(SceneManager)->render(_hBackDC);
	// 3. display	
	::BitBlt(_hDC, 0,0, SCREEN_WIDTH,SCREEN_HEIGHT,
			_hBackDC,0,0, SRCCOPY);

 //	::TransparentBlt();
	//::StretchBlt();
	//::PlgBlt();
	//::AlphaBlend();
 }
void Core::createGDI()
{
	// HOLLOW
	_colorBrushes[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	_colorBrushes[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	_colorBrushes[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	_colorBrushes[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	_colorBrushes[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));

	//RED GREEN BLUE PEN
	_colorPens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	_colorPens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	_colorPens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	_colorPens[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	_colorPens[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}
