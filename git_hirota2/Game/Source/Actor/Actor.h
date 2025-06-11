#pragma once

#include "Source/Transform/Transform.h"
namespace nsGame {
    class Actor : public IGameObject
    {
    public:
        Actor();
        ~Actor();
        virtual bool Start() override;
        virtual void Update() override;
        virtual void Render(RenderContext& rc) override;
    protected:  //本クラスで作成した変数は、派生クラスで関数越しにアクセスせず、直接変数にアクセスしてもよい。
        ModelRender m_modelRender;  //モデルレンダラー。
        std::shared_ptr<nsEngine::Transform> m_transform; // 位置や回転などの変換情報を管理する。

    };
}
