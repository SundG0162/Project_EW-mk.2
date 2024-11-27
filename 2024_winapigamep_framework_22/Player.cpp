#include "pch.h"
#include "Player.h"

Player::Player(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY)
{
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::render(HDC hdc)
{
}
