#include "stdafx.h"
#include "Stage.h"
#include "Transform/Transform.h"
#include <memory>

Stage::Stage()
{
    m_transform = std::make_shared<Transform>();
}

Stage::~Stage()
{
    m_transform.reset();
}

bool Stage::Start()
{
    return true;
}

void Stage::Update()
{
}

void Stage::Render(RenderContext& rc)
{
}
