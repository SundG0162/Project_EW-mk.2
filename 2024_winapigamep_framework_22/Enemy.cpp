#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
	: _moveVector(0.f, 0.f)
	, _maxHealth(5.f)
	, _curHealth(5.f)
{
}

Enemy::~Enemy()
{
}

void Enemy::update()
{



}

void Enemy::render(HDC hdc)
{


}

void Enemy::Move()
{
}

void Enemy::GetDamage(float damage)
{
}

void Enemy::GetStunned(float time)
{
}
