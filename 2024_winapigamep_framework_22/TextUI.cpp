#include "pch.h"
#include "TextUI.h"

TextUI::TextUI(const Vector2& position, const Vector2& size) : UI(position, size)
{
}

TextUI::~TextUI()
{
}

void TextUI::update()
{
	WindowObject::update();
}

void TextUI::render(HDC hdc)
{
	utils::Drawer::renderText(hdc, _position, _text);
}