#include "pch.h"
#include "GDISelector.h"
#include "Core.h"
GDISelector::GDISelector(HDC _hdc, PEN_TYPE _ePen)
	: _hDC(_hdc)
	, _hDefaultBrush(nullptr)
	, _hDefaultPen(nullptr)
	, _hDefaultFont(nullptr)
	, _hFont(nullptr)
{
	HPEN hColorPen = Core::GetInstance()->getPen(_ePen);
	_hDefaultPen = (HPEN)SelectObject(_hdc, hColorPen);
}

GDISelector::GDISelector(HDC _hdc, BRUSH_TYPE _eBrush)
	: _hDC(_hdc)
	, _hDefaultBrush(nullptr)
	, _hDefaultPen(nullptr)
	, _hDefaultFont(nullptr)
	, _hFont(nullptr)
{
	HBRUSH hColorBrush = Core::GetInstance()->getBrush(_eBrush);
	_hDefaultBrush = (HBRUSH)SelectObject(_hdc, hColorBrush);
}

GDISelector::GDISelector(HDC _hdc, HFONT _font)
	: _hDC(_hdc)
	, _hDefaultBrush(nullptr)
	, _hDefaultPen(nullptr)
	, _hDefaultFont(nullptr)
	, _hFont(nullptr)
{
	_hFont = _font;
	_hDefaultFont = (HFONT)SelectObject(_hdc, _hFont);
	SetBkMode(_hdc, TRANSPARENT);
}

GDISelector::~GDISelector()
{
	SelectObject(_hDC, _hDefaultPen);
	SelectObject(_hDC, _hDefaultBrush);
	SelectObject(_hDC, _hDefaultFont);
	if (nullptr != _hFont)
		DeleteObject(_hFont);
}

