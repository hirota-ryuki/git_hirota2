/**
 * キャラクターの基底クラス 
 */
#pragma once
#include "Actor/Actor.h"


namespace nsApp {
    namespace nsActor {
        class Character : public Actor
        {
        public:
            Character();
            virtual ~Character();


        public:
            virtual bool Start() override;
            virtual void Update() override;
            virtual void Render(RenderContext& rc) override;
        };
    }
}
