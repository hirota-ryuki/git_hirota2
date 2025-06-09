#pragma once

class Transform;

class Stage :
    public IGameObject
{
public:
    Stage();
    ~Stage();
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

private:
    std::shared_ptr<Transform> m_transform; // 位置や回転などの変換情報を管理する。
};

