#pragma once
#include "Enemy.h"
class LongHead :
    public Enemy
{
public:
    LongHead();
    LongHead(const Vector2& pos, Object* target);
    ~LongHead();


    void update() override;
    void render(HDC hdc) override;

};

