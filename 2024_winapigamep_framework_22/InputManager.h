#pragma once
enum class KEY_TYPE
{
	LEFT, RIGHT, UP, DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	CTRL, LALT, LSHIFT, SPACE,
	ENTER, TAB, ESC, LBUTTON, RBUTTON,
	NUM_1, NUM_2, NUM_3,
	NUM_4, NUM_5, NUM_6,
	NUM_7, NUM_8, NUM_9,
	KEYPADNUM_1, KEYPADNUM_2, KEYPADNUM_3,
	KEYPADNUM_4, KEYPADNUM_5, KEYPADNUM_6,
	KEYPADNUM_7, KEYPADNUM_8, KEYPADNUM_9,
	LAST
};
enum class KEY_STATE
{					
	NONE, DOWN, UP, PRESS, END
};
struct KeyInfo
{
	KEY_STATE state;
	bool isPrevCheck;
};

class InputManager
{
	DECLARE_SINGLETON(InputManager);
public:
	void init();
	void update();
	const KEY_STATE& getKey(KEY_TYPE _eKey) const
	{
		return _keys[(int)_eKey].state;
	}
	const POINT& getMousePos() const { return _mousePoint; }
private:
	POINT			 _mousePoint = {};
	vector<KeyInfo> _keys;
	int				 _vkKeys[(int)KEY_TYPE::LAST] =
	{ VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 'Q','W','E','R',
	'T','Y','U','I','O','P',
	'A','S','D','F','G','H','J','K','L',
	'Z','X','C','V','B','N','M',
	VK_CONTROL, VK_LMENU, VK_LSHIFT, VK_SPACE,
		VK_RETURN, VK_TAB, VK_ESCAPE,
		VK_LBUTTON, VK_RBUTTON,
		'1','2','3','4','5','6','7','8','9',
		VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3,
		VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6,
		VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9};
};

