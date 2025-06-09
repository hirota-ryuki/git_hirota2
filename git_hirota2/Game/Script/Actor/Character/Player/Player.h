#pragma once
#include "Actor/Character/Character.h"

class Player :
    public Character
{
    Player();
    ~Player();
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;
};

