#pragma once
class GDISelector
{
public:
	GDISelector(HDC _hdc, PEN_TYPE _ePen);
	GDISelector(HDC _hdc, BRUSH_TYPE _eBrush);
	GDISelector(HDC _hdc, HFONT _font);
	~GDISelector();
private:
	HDC		_hDC;
	HPEN	_hDefaultPen;
	HBRUSH	_hDefaultBrush;
	HFONT   _hDefaultFont;
	HFONT	_hFont;
};
