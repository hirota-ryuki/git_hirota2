#pragma once

namespace nsGame {
    struct CellBinary {

        Vector3	vertexPos[3];	// セルの頂点のポジション。
        int		linkCellNo[3];	// セルに隣接しているセル番号。
        Vector3	centerPos;		// セルの中心座標のポジション。
    };

    // セルクラス。
    struct Cell {
        enum State {
            State_NotResearch,
            State_Opened,
            State_Closed,
        };

        Vector3	vertexPos[3];

        Cell* linkCells[3];	    // セルに隣接しているセル。
        Vector3	centerPos;		// セルの中心座標のポジション。
        int	    linkMax = 0;	// 隣接しているセルの数。
        float	costFromStart;
        float	costToGoal;
        Cell* parentCell;
        State	state = State_NotResearch;
    };

    class Navmesh : public IGameObject
    {
    public:
        Navmesh();
        ~Navmesh();

        bool Start() override { return true; }
        void Update() override;
        void Render(RenderContext& rc) override;

        /// <summary>
        /// ナビメッシュを初期化する。
        /// </summary>
        void Init();

        /// <summary>
        /// モデルからナビメッシュを作成する。
        /// </summary>
        /// <param name="model">ナビメッシュ作成元のモデル。</param>
        void Create(ModelRender& model);

        /// <summary>
        /// モデルから頂点バッファとインデックスバッファを作成する。
        /// </summary>
        /// <param name="model">バッファ作成元のモデル。</param>
        void BuildVertexBufferAndIndexBufferFrom(ModelRender& model);

        /// <summary>
        /// モデルから頂点情報を構築する。
        /// </summary>
        /// <param name="model">頂点情報作成元のモデル。</param>
        void BuildVertex(Model& model);

        /// <summary>
        /// モデルからインデックス情報を構築する。
        /// </summary>
        /// <param name="model">インデックス情報作成元のモデル。</param>
        void BuildIndex(Model& model);

    private:
        using NavVertexBuffer = std::vector<Vector3>;	// 頂点バッファ。
        using NavIndexBuffer = std::vector<unsigned int>;	// インデックスバッファ。

        using NavVertexBufferPtr = std::unique_ptr<NavVertexBuffer>;
        using NavIndexBufferPtr = std::unique_ptr<NavIndexBuffer>;

        std::vector<NavVertexBufferPtr>	m_vertexBufferArray; // 頂点バッファ。
        std::vector<NavIndexBufferPtr>		m_indexBufferArray;	 // インデックスバッファ。
    };
}
