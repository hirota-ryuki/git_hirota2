#pragma once

namespace nsGame {


    //これを定義するとナビメッシュのデータが再作成される。
    //背景データに変更が入ったときに有効にしてください。
    
    #define REBUILD_NAVIMESH_DATA		
    
    //これを定義すると、ナビメッシュのデバッグ表示が有効になる。
    #ifdef _DEBUG
    #define USE_NAVIMESH_DEBUG	//Debug。
    #else
    //#define USE_NAVIMESH_DEBUG	//Release.
    #endif

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
        Navmesh() {};
        ~Navmesh() {};

        void Update() override;

        /// <summary>
        /// ナビメッシュを初期化する。
        /// </summary>
        void Init(ModelRender& model);

        /// <summary>
        /// モデルからナビメッシュを作成する。
        /// </summary>
        /// <param name="model">ナビメッシュ作成元のモデル。</param>
        void Create(ModelRender& model);

        /// <summary>
        /// セルのポインタのベクターを取得する。
        /// </summary>
        /// <returns>Cell 型へのポインタの std::vector への定数参照。</returns>
        const std::vector<Cell*>& GetCell() const
        {
            return m_cells;
        }
    private:
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

        /// <summary>
        /// セルを構築する。
        /// </summary>
        void BuildCells();

        /// <summary>
        /// セルの隣接情報を構築する。
        /// </summary>
        void BuildLinkCellInfo();

        /// <summary>
        /// セルの隣接情報を構築する。(マルチスレッド)
        /// </summary>
        /// <param name="startCellNo">開始セルの番号。</param>
        /// <param name="endCellNo">終了セルの番号。</param>
        void BuildLinkCellInfo(int startCellNo, int endCellNo);

        /// <summary>
        /// ナビメッシュを外部データとして保存。
        /// </summary>
        void Save();

        /// <summary>
        /// 保存されたバイナリデータからナビメッシュを構築。
        /// </summary>
        void BuildNavmeshFromBinary();
    private:
        using NavVertexBuffer = std::vector<Vector3>;	    // 頂点バッファ。
        using NavIndexBuffer = std::vector<unsigned int>;	// インデックスバッファ。
        using NavVertexBufferPtr = std::unique_ptr<NavVertexBuffer>;
        using NavIndexBufferPtr = std::unique_ptr<NavIndexBuffer>;
        std::vector<NavVertexBufferPtr>	m_vertexBufferArray; // 頂点バッファ。
        std::vector<NavIndexBufferPtr>	m_indexBufferArray;	 // インデックスバッファ。

        std::vector<Cell*>	m_cells;		//セルの配列。
        BoxCollider			m_collider;		//セル用のカプセルコライダー。

        //デバッグ関係。
        std::vector<std::shared_ptr<ModelRender>>	m_debugModelList;				//デバッグモデルの配列。
        bool    m_isDebug = false;				//デバッグモードのオンオフ。
        bool    m_isChangeActiveModel = false;	//デバッグモードのオンオフ。
        bool    m_isCreateModel = false;		//デバッグモデルを作ったかどうか。
    };
}
