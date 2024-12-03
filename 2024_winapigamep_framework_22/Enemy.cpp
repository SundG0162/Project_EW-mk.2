#include "pch.h"
#include "Enemy.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "Collider.h"
#include "SpriteRenderer.h"
#include "Sprite.h"

Enemy::Enemy()
	: _moveVector(0.f, 0.f)
	, _maxHealth(5.f)
	, _curHealth(5.f)
	, _moveSpeed(50.f)
	, _isMovable(true)
	,_stunTime(0.f)
	, _target(nullptr)
{

	/*Texture* texture = GET_SINGLETON(ResourceManager)->textureFind(L"Filename");
	Sprite* sprite = utils::SpriteParser::textureToSprite(texture);
	SpriteRenderer* spriteRenderer = addComponent<SpriteRenderer>();
	spriteRenderer->setSprite(sprite);*/

	addComponent<Collider>(); // ���ڽ� ũ�� ����ȭ �������
	SetRandomPos();
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	componentUpdate();
	Move();
	if (_whiteTimer > 0)
	{
		_whiteTimer -= DELTATIME;
		if (_whiteTimer <= 0)
		{
			getComponent<SpriteRenderer>()->setWhiteness(false);
		}
	}
}

void Enemy::render(HDC hdc)
{
	componentRender(hdc);
	SpriteRenderer* sp = getComponent<SpriteRenderer>();
	int height = sp->getSprite()->getSize().y * sp->getScale().y;
	RECT_render(hdc, getPosition().x, getPosition().y - height, 20, 20);
}

void Enemy::Move()
{
	if (!_isMovable)
	{
		_stunTime -= DELTATIME;
		if (_stunTime < 0) _isMovable = true;
		return;
	}
	Vector2 targetpos = _target->getPosition();
	Vector2 direction = targetpos - _position;
	direction.Normalize();
	_moveVector = direction * (_moveSpeed * DELTATIME);
	DoMove(_moveVector);
}

void Enemy::DoMove(Vector2& vec)
{
	_position = _moveVector + _position;
}


void Enemy::GetDamage(int damage)
{
	_curHealth -= damage;
	getComponent<SpriteRenderer>()->setWhiteness(true);
	_whiteTimer = 0.2f;
	if (_curHealth <= 0)
	{
		_isDead = true;
		GET_SINGLETON(EventManager)->deleteObject(this);
	}
}

void Enemy::GetStunned(float time)
{
	_stunTime = max(_stunTime, time);
	_isMovable = false;
}
