#pragma once
#include "Actor/Character/Character.h"
namespace nsGame {
    class BattleCharacter :
        public Character
    {
        BattleCharacter();
        ~BattleCharacter();
        bool Start() override;
        void Update() override;
        void Render(RenderContext& rc) override;
    };
}
