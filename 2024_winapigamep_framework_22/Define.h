#pragma once
// 매크로

#define DECLARE_SINGLETON(type)	 \
private:						\
	type() {}					\
public:							\
	static type* GetInstance()	\
	{							\
		static type m_pInst;	\
		return &m_pInst;		\
	}							\

#define GET_SINGLETON(type) type::GetInstance()
#define fDT GET_SINGLETON(TimeManager)->GetDT()

#define KEY_CHECK(key, state) InputManager::GetInstance()->getKey(key) == state
#define GET_KEYNONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define GET_KEYUP(key) KEY_CHECK(key, KEY_STATE::UP)
#define GET_KEYDOWN(key) KEY_CHECK(key, KEY_STATE::DOWN)
#define GET_KEY(key) KEY_CHECK(key, KEY_STATE::PRESS)
#define GET_MOUSEPOS GET_SINGLETON(InputManager)->getMousePos()
// render 매크로
#define RECT_render(hdc, posx, posy, sizex, sizey) Rectangle(hdc, (int)(posx-sizex/2), (int)(posy-sizey/2), (int)(posx+sizex/2), (int)(posy+sizey/2))
#define ELLIPSE_render(hdc, posx, posy, sizex, sizey) Ellipse(hdc, (int)(posx-sizex/2), (int)(posy-sizey/2), (int)(posx+sizex/2), (int)(posy+sizey/2))
#define RECT_MAKE(posx, posy, sizex, sizey) {posx-sizex/2, posy-sizey/2, posx+sizex/2, posy+sizey/2}
