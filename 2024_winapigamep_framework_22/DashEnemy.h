#pragma once
#include "SkillEnemy.h"
class StatComponent;
class DashEnemy :
    public SkillEnemy
{
    using Super = SkillEnemy;
public:
    DashEnemy(Object* target);
    ~DashEnemy();

    virtual void update() override;
    virtual void render(HDC hdc) override;

    virtual void startSkill();
    virtual void updateSkill();
    virtual void endSkill();

private:
    StatComponent* sc;
};

