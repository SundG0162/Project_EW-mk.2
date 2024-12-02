#pragma once
class Sprite;
class Texture;
namespace utils
{
	static const float PI = 3.141592f;
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
	class Ease
	{
	public:
		static float inSine(float x) { return 1 - cosf((x * PI) / 2); }
		static float outSine(float x) { return sinf((x * PI) / 2); }
		static float inOutSine(float x) { return -(cosf(PI * x) - 1) / 2; }
		static float inQuad(float x) { return x * x; }
		static float outQuad(float x) { return 1 - (1 - x) * (1 - x); }
		static float inOutQuad(float x) { return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2.f; }
		static float inCubic(float x) { return x * x * x; }
		static float outCubic(float x) { return 1 - pow(1 - x, 3); }
		static float inOutCubic(float x) { return x < 0.5f ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2; }
	};
	class CoordinateSync
	{
		static const Vector2& nonClientToClient(const RECT& windowRect, const Vector2& position);
	};
};