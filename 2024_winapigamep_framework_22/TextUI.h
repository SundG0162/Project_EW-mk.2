#pragma once
#include "UI.h"
class TextUI : public UI
{
public:
	TextUI();
	~TextUI();
public:
	void init(const wstring& text) { _text = text; };
	void setupFont(const wstring& fontName, float fontSize, float fontWeight);
	void setColor(const COLORREF& color) { _color = color; }
	void setText(const wstring& text) { _text = text; }
public:
	void update() override;
	void render(HDC hdc) override;
private:
	wstring _text;
	COLORREF _color;
	HFONT _hFont;
	SIZE _size;
};