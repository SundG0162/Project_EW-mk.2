#include "pch.h"
#include "CCTV.h"

CCTV::CCTV(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY)
{
}

CCTV::~CCTV()
{
}

void CCTV::update()
{
}

void CCTV::render(HDC hdc)
{
}
