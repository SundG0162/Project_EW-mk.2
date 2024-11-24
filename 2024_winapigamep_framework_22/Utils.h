#pragma once
class Sprite;
class Texture;
namespace utils
{
	class SpriteParser
	{
	public:
		static Sprite* textureToSprite(Texture* texture);
		static Sprite* textureToSprite(Texture* texture, Vector2 leftTop, Vector2 sliceSize);
		static vector<Sprite*> textureToSprites(Texture* texture, Vector2 leftTop, Vector2 sliceSize, Vector2 step);
	};
	class Drawer
	{
	public:
		static void renderText(HDC hdc, Vector pos, const wstring& str);
		static void renderRect(HDC hdc, Vector pos, int32 width, int32 height);
		static void renderRectColor(HDC hdc, Vector pos, int32 width, int32 height, COLORREF brushColor, COLORREF penColor);
		static void renderCircle(HDC hdc, Vector pos, int32 radius);
		static void renderCircleColor(HDC hdc, Vector pos, int32 radius, COLORREF brushColor, COLORREF penColor);
		static void renderLine(HDC hdc, Vector from, Vector to);
		static void renderLineColor(HDC hdc, Vector from, Vector to, COLORREF color);
	};
};