/**
 * ステージクラス
 */
#pragma once
#include "Source/Actor/Actor.h"


namespace nsApp {
    namespace nsActor {
        /**
         * ステージクラス
         */
        class Stage : public Actor
        {
        public:
            Stage();
            ~Stage();


        public:
            bool Start() override;
            void Update() override;
            void Render(RenderContext& rc) override;
        };
    }
}
