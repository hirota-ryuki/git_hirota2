#include "stdafx.h"
#include "Stage.h"
#include "Transform/Transform.h"

Stage::Stage()
{
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
