#pragma once
#include "Object.h"
class TestObject :
    public Object
{
    // Inherited via Object
    void update() override;
    void render(HDC hdc) override;
};

