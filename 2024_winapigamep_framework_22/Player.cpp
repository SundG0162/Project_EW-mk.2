#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "CCTV.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Sprite.h"

Player::Player(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY)
{
	_window->setCloseable(false);
	_cctv = nullptr;
	SpriteRenderer* spriteRenderer = addComponent<SpriteRenderer>();
	Sprite* sprite = utils::SpriteParser::textureToSprite(GET_SINGLETON(ResourceManager)->textureFind(L"Computer"));
	spriteRenderer->setSprite(sprite);
	spriteRenderer->setScale({ 3,3 });
}

Player::~Player()
{
}

void Player::update()
{
	Vector2 movement = {};
	if (GET_KEY(KEY_TYPE::W))
		movement.y -= 1;
	if (GET_KEY(KEY_TYPE::A))
		movement.x -= 1;
	if (GET_KEY(KEY_TYPE::S))
		movement.y += 1;
	if (GET_KEY(KEY_TYPE::D))
		movement.x += 1;
	movement.Normalize();
	movement *= 300 * DELTATIME;
	_cctv->localMove(movement);
}

void Player::render(HDC hdc)
{
	componentRender(hdc);
}
