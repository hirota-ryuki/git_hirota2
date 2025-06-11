#pragma once
#include "Actor/Actor.h"
namespace nsGame {
    class Stage :
        public Actor

    {
    public:
        Stage();
        ~Stage();
        bool Start() override;
        void Update() override;
        void Render(RenderContext& rc) override;

    private:
    };
}
