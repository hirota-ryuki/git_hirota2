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
};

