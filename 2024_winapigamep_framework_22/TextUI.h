#pragma once
#include "UI.h"
class TextUI : public UI
{
public:
	TextUI(const Vector2& position, const Vector2& size);
	~TextUI();
public:
	void init(const wstring& text) { _text = text; };
public:
	void update() override;
	void render(HDC hdc) override;
private:
	wstring _text;
};