#pragma once
#include "Object.h"
class WindowObject;
class Enemy :
    public Object
{
public:
    Enemy();
    virtual ~Enemy();
    // Inherited via Object
    virtual void update() override;
    virtual void render(HDC hdc) override;

    void Move();
    void GetDamage(int damage);
    void GetStunned(float time) ;

    void SetRandomPos() { setPosition(utils::ExMath::getRandomVector() * posScale); }
    void SetMaxHP(float hp) { _maxHealth = hp; _curHealth = hp; }
    void SetTarget(Object* target) { _target = target; }

private:
    Vector2 posScale = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
    Vector2 _moveVector;
    float _whiteTimer;
    int _maxHealth;
    int _curHealth;
    bool _isMovable;
    float _moveSpeed;
    float _stunTime;
    Object* _target;
};

