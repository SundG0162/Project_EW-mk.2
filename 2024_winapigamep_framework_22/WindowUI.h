#pragma once
#include "WindowObject.h"
class UI;
class WindowUI : public WindowObject
{
public:
	WindowUI(const Vector2& position, const Vector2& size, WINDOW_TYPE type, const wstring& name);
	~WindowUI();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	UI* getUI() { return _ui; }
	void setUI(UI* ui) { _ui = ui; }
private:
	UI* _ui;
};

