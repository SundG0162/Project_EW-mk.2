#include "pch.h"
#include "InputManager.h"
#include "Core.h"
void InputManager::init()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		_keys.push_back(KeyInfo{KEY_STATE::NONE, false});
}

void InputManager::update()
{

	//GetActiveWindow(); // 창을 여러개 띄울때 맨 위에있는 윈도우
	HWND hWnd = GetFocus(); // 지금 딱 포커싱한거
	if (hWnd == nullptr)
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			_keys[i].isPrevCheck = false;
			_keys[i].state = KEY_STATE::NONE;
		}
		return;
	 }
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		// 키가 눌렸다.
		if (GetAsyncKeyState(_vkKeys[i]))
		{
			// 이전에 눌렸어
			if (_keys[i].isPrevCheck)
				_keys[i].state = KEY_STATE::PRESS;
			else // 이전에 안눌렸어. 지금 딱!!! 누름
				_keys[i].state = KEY_STATE::DOWN;
			_keys[i].isPrevCheck = true;
		}
		// 키가 안눌렸다.
		else
		{
			// 이전에 눌려있었다.
			if (_keys[i].isPrevCheck)
				_keys[i].state = KEY_STATE::UP;
			else
				_keys[i].state = KEY_STATE::NONE;
			_keys[i].isPrevCheck = false;
		}
	}
	// Mouse
	::GetCursorPos(&_mousePoint); // 마우스 좌표 받기
	// 우리가 가진 윈도우 창 기준으로 좌표 변경
	::ScreenToClient(GET_SINGLETON(Core)->getHWnd(), &_mousePoint);


}
