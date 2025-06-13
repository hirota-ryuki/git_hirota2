#include "stdafx.h"
#include "Actor.h"
#include "Source/Transform/Transform.h"
#include <memory>

namespace nsGame {
    //ヘッダで宣言した変数は、ヘッダで初期化するのではなく、コンストラクタで初期化すること。
    //ローカル環境の話になるが、コンパイル時間を減らすためである。
    //例：変数の初期値を変えた時、
    //ヘッダをインクルードしている全てのソースファイルが再コンパイルされてしまうため、
    //コンパイル時間がその分長くなってしまう。
    Actor::Actor()
    {
        m_transform = std::make_shared<nsEngine::Transform>();
    }

    Actor::~Actor()
    {
        m_transform.reset();
    }

    bool Actor::Start()
    {
        return true;
    }

    void Actor::Update()
    {
    }

    void Actor::Render(RenderContext& rc)
    {
    }
}
