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

	//GetActiveWindow(); // â�� ������ ��ﶧ �� �����ִ� ������
	HWND hWnd = GetFocus(); // ���� �� ��Ŀ���Ѱ�
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
		// Ű�� ���ȴ�.
		if (GetAsyncKeyState(_vkKeys[i]))
		{
			// ������ ���Ⱦ�
			if (_keys[i].isPrevCheck)
				_keys[i].state = KEY_STATE::PRESS;
			else // ������ �ȴ��Ⱦ�. ���� ��!!! ����
				_keys[i].state = KEY_STATE::DOWN;
			_keys[i].isPrevCheck = true;
		}
		// Ű�� �ȴ��ȴ�.
		else
		{
			// ������ �����־���.
			if (_keys[i].isPrevCheck)
				_keys[i].state = KEY_STATE::UP;
			else
				_keys[i].state = KEY_STATE::NONE;
			_keys[i].isPrevCheck = false;
		}
	}
	// Mouse
	::GetCursorPos(&_mousePoint); // ���콺 ��ǥ �ޱ�
	// �츮�� ���� ������ â �������� ��ǥ ����
	::ScreenToClient(GET_SINGLETON(Core)->getHWnd(), &_mousePoint);


}
