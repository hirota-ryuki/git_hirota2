/**
 * バトルキャラクタークラス 
 */
#pragma once
#include "Actor/Character/Character.h"


namespace nsApp {
    namespace nsActor {
        /**
         *　バトルキャラクタークラス
         */
        class BattleCharacter : public Character
        {
        public:
            BattleCharacter();
            ~BattleCharacter();


        public:
            bool Start() override;
            void Update() override;
            void Render(RenderContext& rc) override;
        };
    }
}
