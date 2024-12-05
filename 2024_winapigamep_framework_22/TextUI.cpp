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
	_hFont = CreateFontW(fontSize, 0, 0, 0, 0, 0, 0, 0
		, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, fontName.c_str());
}

void TextUI::update()
{
}

void TextUI::render(HDC hdc)
{
	if (_text == L"") return;
	HFONT prevFont = (HFONT)SelectObject(hdc, _hFont);
	SetBkColor(hdc, TRANSPARENT);
	COLORREF prevColor = SetTextColor(hdc, _color);
	vector<wstring> lines = utils::TextEditor::textSplit(_text);
	GetTextExtentPoint(hdc, lines[0].c_str(), lines[0].size(), &_size);
	for (int i = 0; i < lines.size(); i++)
	{
		TextOut(hdc, _position.x - _size.cx / 2, _position.y + _size.cy / 2* i, lines[i].c_str(), lines[i].length());
	}
	SetTextColor(hdc, prevColor);
	SelectObject(hdc, prevFont);
}