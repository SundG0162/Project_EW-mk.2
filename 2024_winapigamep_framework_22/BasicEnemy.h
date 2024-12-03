#pragma once
#include "Enemy.h"
class BasicEnemy :
    public Enemy
{
    using Super = Enemy;
public:
    BasicEnemy();
    BasicEnemy(Object* target);
    ~BasicEnemy();

    void init() override;
    void update() override;
    void render(HDC hdc) override;

};

