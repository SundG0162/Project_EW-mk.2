#pragma once
#include "Object.h"
class Enemy :
    public Object
{
public:
    Enemy();
    virtual ~Enemy();
    // Inherited via Object
    void update() override;
    void render(HDC hdc) override;

    void Move();
    void GetDamage(float damage);
    void GetStunned(float time) ;

    void SetMaxHP(float hp) { _maxHealth = hp; _curHealth = hp; }

private:
    Vector2 _moveVector;
    float _maxHealth;
    float _curHealth;

    //Object _target; //이후 플레이어
};

