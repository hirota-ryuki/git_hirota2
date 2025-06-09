#include "stdafx.h"
#include "Navmesh.h"

Navmesh::Navmesh()
{
}

Navmesh::~Navmesh()
{
}

void Navmesh::Update()
{
    // 必要な更新処理があればここに書く。
}

void Navmesh::Render(RenderContext& rc)
{
    // ナビメッシュの描画処理を書く場合はここ。
}

void Navmesh::Create(ModelRender& model)
{
    BuildVertexBufferAndIndexBufferFrom(model);
}

void Navmesh::BuildVertexBufferAndIndexBufferFrom(ModelRender& model)
{
    Model& modelData = model.GetModel();

    // モデルデータから頂点バッファを構築する。
    BuildVertex(modelData);
    // モデルデータからインデックスバッファを構築する。
    BuildIndex(modelData);
}

void Navmesh::BuildVertex(Model& model)
{
    // メッシュごとに処理するラムダ式。
    model.GetTkmFile().QueryMeshParts([this](const TkmFile::SMesh& mesh)
        {
            // 頂点バッファを作成して座標を格納する。
            VertexBufferPtr vertexBuffer = std::make_unique<VertexBuffer>();
            // メッシュ内の全頂点を処理。
            for (const auto& vertex : mesh.vertexBuffer)
            {
                vertexBuffer->push_back(vertex.pos);
            }
            // バッファ配列に追加。
            m_vertexBufferArray.push_back(std::move(vertexBuffer));
        });
}

void Navmesh::BuildIndex(Model& model)
{
    // メッシュごとに処理するラムダ式。
    model.GetTkmFile().QueryMeshParts([this](const TkmFile::SMesh& mesh)
        {
            // メッシュ内の全インデックスバッファ配列を処理。
            for (const auto& index : mesh.indexBuffer32Array)
            {
                // インデックスバッファを作成して値を格納する。
                IndexBufferPtr indexBuffer = std::make_unique<IndexBuffer>();
                // 各インデックス値を処理。
                for (const auto& i : index.indices)
                {
                    indexBuffer->push_back(i);
                }
                // バッファ配列に追加。
                m_indexBufferArray.push_back(indexBuffer);
            }
        });
}
