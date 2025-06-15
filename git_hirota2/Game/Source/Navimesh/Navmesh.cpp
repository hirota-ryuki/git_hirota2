#include "stdafx.h"
#include "Navmesh.h"
#include <memory>
namespace nsGame {
    namespace {
        // 定数定義
        constexpr float COLLIDER_EXPANSION = 2.5f; // カプセルコライダーの拡大率
    }

    void Navmesh::Update()
    {
#ifdef USE_NAVIMESH_DEBUG
        //ボタンで切り替え。
        if (g_pad[0]->IsTrigger(enButtonSelect))
        {
            m_isDebug = !m_isDebug;
            m_isChangeActiveModel = true;
        }

        if (m_isChangeActiveModel) {
            if (m_isDebug) {
                for (auto& model : m_debugModelList) {
                    //model->ActiveMode(true);
                }
            }
            else {
                for (auto& model : m_debugModelList) {
                    //model->ActiveMode(false);
                }
            }
            m_isChangeActiveModel = false;
        }
#endif
    }

    void Navmesh::Init(ModelRender& model)
    {
        //セルの当たり判定用のカプセルコライダー
        //初期化
        //半径が1であるのは後々に三角形の一番長い重心頂点間に拡大するため
    //	m_collider.Create(1.f, 30.f);
#ifdef REBUILD_NAVIMESH_DATA
        Create(model);
#else
    //保存されたバイナリデータからナビメッシュを構築。
        BuildNavmeshFromBinary();
#endif
#ifdef USE_NAVIMESH_DEBUG
        if (!m_isCreateModel) {
            for (auto& all : m_cells)
            {
                std::shared_ptr<ModelRender> debugModel= std::make_shared<ModelRender>();
                debugModel->Init("modelData/debug/debugbox.tkm");
                debugModel->SetPosition(all->centerPos);
                int No = 0;
                if (all->linkCells[No] != NULL)
                {
                    //float dot = all->centerPos.Dot(all->linkCells[2]->centerPos);
                    float dot = all->centerPos.x * all->linkCells[No]->centerPos.x +
                        all->centerPos.y * all->linkCells[No]->centerPos.y +
                        all->centerPos.z * all->linkCells[No]->centerPos.z;
                    float k = atan(dot);
                    Quaternion g;
                    //g.SetRotationDeg(CVector3::AxisX(), 45.0f);
                    g.SetRotation(Vector3::AxisY, k);
                    debugModel->SetRotation(g);
                }
                //m_debugModel->ActiveMode(false);
                m_debugModelList.emplace_back(debugModel);
            }
        }
#endif
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
                NavVertexBufferPtr vertexBuffer = std::make_unique<NavVertexBuffer>();
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
                    NavIndexBufferPtr indexBuffer = std::make_unique<NavIndexBuffer>();
                    // 各インデックス値を処理。
                    for (const auto& i : index.indices)
                    {
                        indexBuffer->push_back(i);
                    }
                    // バッファ配列に追加。
                    m_indexBufferArray.push_back(std::move(indexBuffer));
                }
            });
    }

    struct NMCallBack : public btCollisionWorld::ConvexResultCallback
    {
        /// <summary>
        /// 備考
            //CallBackクラスのコンストラクタ
            //CallBack()
            //初期化リスト
            //{}の前に初期化を行う
            //namespace　btCollisionWorld
            //構造体　ClosestConvexResultCallback
            //ClosestConvexResultCallbackはコンストラクタに引数があるので
            //初期化しなくてはならない
            //{}
        /// </summary>

        //障害物があるかないか判定
        bool isHit = false;
        //衝突したら勝手に呼んでくれる
        virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
        {
            //当たった
            isHit = true;
            return 0;
        }
    };

    void Navmesh::BuildCells()
    {
        //セルに頂点3つと重心を設定し、セルに登録
        //m_vertexBufferArrayとm_indexBufferArrayの要素数は同じ
        for (int i = 0; i < m_indexBufferArray.size(); i++) {
            //インデックスバッファの配列
            //頂点の場所
            auto& indexBuffer = m_indexBufferArray[i];
            //頂点バッファの配列
            //一つの頂点バッファにつき1パーツ
            auto& vertexBuffer = m_vertexBufferArray[i];

            //ポリゴンの数
            //ポリゴンは頂点3つで形成されるので3で割っている
            int numPoly = indexBuffer->size() / 3;
            //ポリゴンの数だけ回す
            for (int polyNo = 0; polyNo < numPoly; polyNo++) {
                //セルの生成
                nsGame::Cell* cell = new Cell;

                //頂点の格納
                {
                    //ポリゴン一個に対する3か所の頂点の場所を割り出す
                    int vertNo_0 = indexBuffer->at(polyNo * 3);
                    int vertNo_1 = indexBuffer->at(polyNo * 3 + 1);
                    int vertNo_2 = indexBuffer->at(polyNo * 3 + 2);
                    //セルに頂点の場所を格納
                    cell->vertexPos[0] = vertexBuffer->at(vertNo_0);
                    cell->vertexPos[1] = vertexBuffer->at(vertNo_1);
                    cell->vertexPos[2] = vertexBuffer->at(vertNo_2);
                }

                //centerPosの登録
                //三角形の重心
                //合計なので初期化
                cell->centerPos = Vector3::Zero;
                cell->centerPos = cell->vertexPos[0] + cell->vertexPos[1] + cell->vertexPos[2];
                cell->centerPos /= 3;

                //カプセルコライダーの半径を
                //三角形の一番長い重心頂点間の長さに拡大

                //重心から頂点までの長さを求める
                //これがカプセルコライダーの半径になる
                Vector3 radius[3];
                for (int i = 0; i < 3; i++)
                {
                    radius[i] = cell->centerPos - cell->vertexPos[i];
                }
                //1番長い距離を比較で求める
                Vector3 maxLength;
                maxLength = radius[0];
                for (int i = 1; i < 3; i++)
                {
                    if (maxLength.Length() < radius[i].Length())
                    {
                        maxLength = radius[i];
                    }
                }
                //カプセルコライダーの半径を拡大
                Vector3 halfSize;
                halfSize.x = maxLength.Length() * COLLIDER_EXPANSION;
                halfSize.z = maxLength.Length() * COLLIDER_EXPANSION;
                halfSize.y = 30.0f;
                m_collider.Create(halfSize);

                //コリジョンの移動の始点と終点の設定
                //btTransformは座標、回転の情報を持っている
                //情報の初期化を行わなければならない
                btTransform start, end;
                {
                    //回転の設定
                    start.setIdentity();
                    end.setIdentity();
                    //座標の設定
                    //Origin 意味：原点
                    start.setOrigin(btVector3(cell->centerPos.x, cell->centerPos.y + 20.f, cell->centerPos.z));
                    end.setOrigin(btVector3(cell->centerPos.x, cell->centerPos.y + 50.f, cell->centerPos.z));
                }

                NMCallBack callback;
                //startからendまでコリジョンを移動させて当たり判定を取る
                PhysicsWorld::GetInstance()->ConvexSweepTest((btConvexShape*)m_collider.GetBody(), start, end, callback);

                if (callback.isHit == false) {
                    //セルに登録
                    m_cells.push_back(cell);
                }
            }
        }
        for (auto& all : m_cells)
        {
            for (int i = 0; i < 3; i++)
            {
                all->linkCells[i] = nullptr;
                all->costFromStart = 0.0f;
                all->costToGoal = 0.0f;
                all->parentCell = nullptr;
            }
        }
    }

    void Navmesh::BuildLinkCellInfo()
    {
#ifdef _DEBUG
        //一つのスレッドで調べるセルの数を計算。
        //Stopwatch sw;
        //sw.Start();
#endif
        int numCellOneThread = m_cells.size() / 3;
#if 1   //これを0にするとシングルスレッドでの隣接セルの構築になります。
        //4スレッドに分担して隣接セル情報を構築する。
        //並列。
        std::thread buildLinkCellThread00([&] {
            BuildLinkCellInfo(0, numCellOneThread);
            });

        std::thread buildLinkCellThread01([&] {
            BuildLinkCellInfo(numCellOneThread, numCellOneThread * 2);
            });

        std::thread buildLinkCellThread02([&] {
            BuildLinkCellInfo(numCellOneThread * 2, numCellOneThread * 3);
            });
        std::thread buildLinkCellThread03([&] {
            BuildLinkCellInfo(numCellOneThread * 3, numCellOneThread * 4);
            });

        buildLinkCellThread00.join();
        buildLinkCellThread01.join();
        buildLinkCellThread02.join();
        buildLinkCellThread03.join();
#else
        //直列。
        BuildLinkCellInfo(0, numCellOneThread);
        BuildLinkCellInfo(numCellOneThread, numCellOneThread * 2);
        BuildLinkCellInfo(numCellOneThread * 2, numCellOneThread * 3);
        BuildLinkCellInfo(numCellOneThread * 3, numCellOneThread * 4);
#endif
#ifdef _DEBUG
        //時間計測。
        //sw.Stop();
        wchar_t text[256];
        //sprintf(text, "build time = %f\n", sw.GetElapsed());
        OutputDebugString(text);
#endif
    }

    void Navmesh::BuildLinkCellInfo(int startCellNo, int endCellNo)
    {
        //登録されたセルの数だけ回す
        for (int cellNo = startCellNo; cellNo < endCellNo && cellNo < m_cells.size(); cellNo++)
        {
            auto all = m_cells[cellNo];

            //同じセルと比較しないようにするためのループ
            for (auto& currentCell : m_cells)
            {

                //同じセルなら処理を除外する
                if (all != currentCell)
                {
                    //座標が一致した頂点をカウント
                    int countSameVertex = 0;
                    //allの頂点の要素を進める
                    for (int i = 0; i < 3; i++)
                    {
                        //allの頂点を格納
                        Vector3 allVPos;
                        allVPos = all->vertexPos[i];

                        //currentCellの頂点の要素を進める
                        for (int j = 0; j < 3; j++)
                        {
                            //allVPosとcurrentVPosの距離
                            Vector3 diff;
                            diff = allVPos - currentCell->vertexPos[j];
                            //もし頂点どうしがほぼ同じ距離にいたら
                            if (diff.Length() <= 0.01f)
                            {
                                //一致した頂点数をカウント
                                countSameVertex++;
                            }
                        }
                    }
                    //２頂点が重複していたら、隣接しているとする。
                    if (countSameVertex == 2) {
                        all->linkCells[all->linkMax] = currentCell;
                        all->linkMax++;

                    }

                }
            }
        }
    }

    void Navmesh::Save()
    {
        FILE* fp = fopen("stage.hnv", "wb");
        if (fp == nullptr) {
            //ファイルオープンに失敗
            MessageBox(nullptr, TEXT("エラー"), TEXT("stage.hnvが開けませんでした。"), MB_OK);
        }
        int cellNum = m_cells.size();
        fwrite(&cellNum, sizeof(int), 1, fp);
        for (auto& cell : m_cells)
        {
            CellBinary cellBinary;
            //頂点。
            for (int i = 0; i < 3; i++) {
                cellBinary.vertexPos[i] = cell->vertexPos[i];
            }
            //隣接セル。
            for (int i = 0; i < 3; i++) {
                int count = 0;
                if (cell->linkCells[i] == nullptr) {
                    cellBinary.linkCellNo[i] = -1;
                }
                else {
                    for (auto itr = m_cells.begin(); itr != m_cells.end(); ++itr) {
                        if (cell->linkCells[i] == *itr) {
                            cellBinary.linkCellNo[i] = count;
                            break;
                        }
                        else if (itr == m_cells.end()) {
                            cellBinary.linkCellNo[i] = -1;
                        }
                        count++;
                    }
                }
            }

            //中心
            cellBinary.centerPos = cell->centerPos;

            fwrite(&cellBinary, sizeof(cellBinary), 1, fp);
        }
        fclose(fp);
    }

    void Navmesh::BuildNavmeshFromBinary()
    {
        //アセットフォルダからナビメッシュのデータをロードする。
        FILE* fp = fopen("stage.hnv", "rb");
        if (fp == nullptr) {
            //ファイルオープンに失敗
            MessageBox(nullptr, TEXT("エラー"), TEXT("stage.hnvが開けませんでした。"), MB_OK);
        }
        int numCell;
        fread(&numCell, sizeof(int), 1, fp);
        //CellBinaryの配列を動的に確保
        CellBinary* cellBinarys = new CellBinary[numCell];
        fread(cellBinarys, sizeof(CellBinary) * numCell, 1, fp);

        //CellBinaryからCellの情報を構築する。
        for (int i = 0; i < numCell; i++) {
            //セルの生成
            Cell* cell = new Cell;

            for (int j = 0; j < 3; j++) {
                cell->vertexPos[j] = cellBinarys[i].vertexPos[j];
            }
            cell->centerPos = cellBinarys[i].centerPos;
            m_cells.push_back(cell);
        }

        for (int i = 0; i < numCell; i++) {
            for (int j = 0; j < 3; j++) {
                if (cellBinarys[i].linkCellNo[j] != -1) {
                    m_cells[i]->linkCells[j] = m_cells[(cellBinarys[i].linkCellNo[j])];
                }
                else {
                    m_cells[i]->linkCells[j] = NULL;
                }
            }
        }
        delete[] cellBinarys;
        fclose(fp);
    }
}
