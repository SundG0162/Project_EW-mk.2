#pragma once
#include "Scene.h"
class EnemyTestScene :
    public Scene
{
public:
    // Inherited via Scene
    void init() override;
    virtual void render(HDC hDC) override;
};

