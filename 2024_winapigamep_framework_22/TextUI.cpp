#include "pch.h"
#include "TextUI.h"
#include "GDISelector.h"

TextUI::TextUI() : UI()
{
	_hFont = nullptr;
	_color = RGB(255, 255, 255);
	_text = L"";
}

TextUI::~TextUI()
{
}

void TextUI::setupFont(const wstring& fontName, float fontSize, float fontWeight)
{
	_hFont = CreateFont(fontSize, 0, 0, 0, 0, 0, 0, 0
		, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, fontName.c_str());
}

void TextUI::update()
{
}

void TextUI::render(HDC hdc)
{
	HFONT prevFont = (HFONT)SelectObject(hdc, _hFont);
	SetBkColor(hdc, TRANSPARENT);
	COLORREF prevColor = SetTextColor(hdc, _color);
	GetTextExtentPoint(hdc, _text.c_str(), _text.size(), &_size);
	TextOut(hdc, _position.x - _size.cx / 2, _position.y - _size.cy / 2, _text.c_str(), _text.length());
	SetTextColor(hdc, prevColor);
	SelectObject(hdc, prevFont);
}