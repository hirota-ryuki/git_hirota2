#pragma once
#include "Actor/Actor.h"

class Character : public Actor
{
public:
    Character();
    ~Character();
    virtual bool Start() override;
    virtual void Update() override;
    virtual void Render(RenderContext& rc) override;
};
