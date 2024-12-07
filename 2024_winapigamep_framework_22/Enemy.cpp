#include "pch.h"
#include "Enemy.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "Collider.h"
#include "SpriteRenderer.h"
#include "Sprite.h"
#include "StatComponent.h"
#include "Stat.h"

Enemy::Enemy()
	: _moveVector(0.f, 0.f)
	, _maxHealth(5.f)
	, _curHealth(5.f)
	, _isMovable(true)
	,_stunTime(0.f)
	, _target(nullptr)
{

	/*Texture* texture = GET_SINGLETON(ResourceManager)->textureFind(L"Filename");
	Sprite* sprite = utils::SpriteParser::textureToSprite(texture);
	SpriteRenderer* spriteRenderer = addComponent<SpriteRenderer>();
	spriteRenderer->setSprite(sprite);*/
}

Enemy::Enemy(Object* target)
{
	addComponent<Collider>(); // ���ڽ� ũ�� ����ȭ �������
	SetRandomPos();
	SetTarget(target);
	stat = addComponent<StatComponent>();
	stat->addStat(L"moveSpeed", new Stat(20.f));
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
}

void Enemy::Move()
{
	{
		Vector2 targetpos = _target->getPosition();
		toTarget = targetpos - _position;
	}
	if (!_isMovable)
	{
		_stunTime -= DELTATIME;
		if (_stunTime < 0) _isMovable = true;
		return;
	}
	Vector2 direction = toTarget;
	direction.Normalize();
	_moveVector = direction * (stat->getStat(L"moveSpeed")->getValue() * DELTATIME);
	DoMove(_moveVector);
}

void Enemy::DoMove(Vector2& vec)
{
	_position = vec + _position;
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

