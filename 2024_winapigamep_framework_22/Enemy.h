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
    void DoMove(Vector2& vec);
    void GetDamage(int damage);
    void GetStunned(float time) ;

    void SetRandomPos() { setPosition(utils::ExMath::getRandomVector() * posScale); }
    void SetMaxHP(float hp) { _maxHealth = hp; _curHealth = hp; }
    void SetTarget(Object* target) { _target = target; }

protected:
    Vector2 _moveVector;
    Vector2 posScale = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
    int _maxHealth;
    int _curHealth;
    float _moveSpeed;
    Object* _target;
private:
    bool _isMovable;
    float _whiteTimer;
    float _stunTime;
};

