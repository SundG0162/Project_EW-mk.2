#include "pch.h"
#include "Utils.h"
#include "Sprite.h"
#include "Texture.h"

void utils::Drawer::renderText(HDC hdc, Vector pos, const wstring& str)
{
    ::TextOut(hdc, pos.x, pos.y, str.c_str(), str.length());
}

void utils::Drawer::renderRect(HDC hdc, Vector pos, int32 width, int32 height)
{
    ::Rectangle(hdc
        , pos.x - width / 2
        , pos.y - height / 2
        , pos.x + width / 2
        , pos.y + height / 2
    );
}

void utils::Drawer::renderRectColor(HDC hdc, Vector pos, int32 width, int32 height, COLORREF brushColor, COLORREF penColor)
{
    HPEN pen = CreatePen(PS_SOLID, 1, penColor);
    HBRUSH brush = CreateSolidBrush(brushColor);
    HPEN prevPen = (HPEN)SelectObject(hdc, pen);
    HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, brush);
    ::Rectangle(hdc
        , pos.x - width / 2
        , pos.y - height / 2
        , pos.x + width / 2
        , pos.y + height / 2
    );
    SelectObject(hdc, prevPen);
    SelectObject(hdc, prevBrush);
    DeleteObject(pen);
    DeleteObject(brush);
}

void utils::Drawer::renderCircle(HDC hdc, Vector pos, int32 radius)
{
    ::Ellipse(hdc
        , pos.x - radius / 2
        , pos.y - radius / 2
        , pos.x + radius / 2
        , pos.y + radius / 2
    );

}

void utils::Drawer::renderCircleColor(HDC hdc, Vector pos, int32 radius, COLORREF brushColor, COLORREF penColor)
{
    HPEN pen = CreatePen(PS_SOLID, 1, penColor);
    HBRUSH brush = CreateSolidBrush(brushColor);
    HPEN prevPen = (HPEN)SelectObject(hdc, pen);
    HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, brush);
    ::Ellipse(hdc
        , pos.x - radius / 2
        , pos.y - radius / 2
        , pos.x + radius / 2
        , pos.y + radius / 2
    );
    SelectObject(hdc, prevPen);
    SelectObject(hdc, prevBrush);
    DeleteObject(pen);
    DeleteObject(brush);
}

void utils::Drawer::renderLine(HDC hdc, Vector from, Vector to)
{
    ::MoveToEx(hdc, from.x, from.y, nullptr);
    ::LineTo(hdc, to.x, to.y);
}

void utils::Drawer::renderLineColor(HDC hdc, Vector from, Vector to, COLORREF color)
{
    HPEN hPen = ::CreatePen(PS_SOLID, 1, color);
    HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);
    ::MoveToEx(hdc, from.x, from.y, nullptr);
    ::LineTo(hdc, to.x, to.y);

    ::SelectObject(hdc, hOldPen);
    ::DeleteObject(hPen);

}

Sprite* utils::SpriteParser::textureToSprite(Texture* texture)
{
    Sprite* sprite = new Sprite(texture, 0,0, texture->getWidth(), texture->getHeight());
    return sprite;
}

Sprite* utils::SpriteParser::textureToSprite(Texture* texture, Vector2 leftTop, Vector2 sliceSize)
{
    Sprite* sprite = nullptr;
    sprite = new Sprite(texture, leftTop.x, leftTop.y, sliceSize.x, sliceSize.y);
    return sprite;
}

vector<Sprite*> utils::SpriteParser::textureToSprites(Texture* texture, Vector2 leftTop, Vector2 sliceSize, Vector2 step)
{
    vector<Sprite*> sprites;
    while (true)
    {
        Sprite* sprite = textureToSprite(texture, leftTop, sliceSize);
        leftTop.x += step.x;
        LONG width = texture->getWidth();
        sprites.push_back(sprite);
        if (leftTop.x + sliceSize.x > width)
            break;
    }
    return sprites;
}

const Vector2& utils::CoordinateSync::nonClientToClient(const RECT& windowRect, const Vector2& position)
{
    RECT clientRect = windowRect;
    AdjustWindowRect(&clientRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);
    Vector2 fixedPosition;
    fixedPosition.x = position.x - (windowRect.left - clientRect.left);
    fixedPosition.y = position.y - (windowRect.top - clientRect.top);
    return fixedPosition;
}

utils::ExMath::ExMath()
{
    mt.seed(rd());
}

float utils::ExMath::getRandomValue(float maxValue)
{
    std::uniform_int_distribution<float> ran(0.f, maxValue);
    return ran(mt);
}