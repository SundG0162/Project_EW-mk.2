#include "pch.h"
#include "TextUI.h"

TextUI::TextUI(const Vector2& position, const Vector2& size, WINDOW_TYPE type) : UI(position, size, type)
{
}

TextUI::~TextUI()
{
}

void TextUI::update()
{
}

void TextUI::render(HDC hdc)
{
	utils::Drawer::renderText(hdc, _position, _text);
}