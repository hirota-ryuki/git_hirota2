/**
 * Actor.h
 * 見た目を持つゲームオブジェクトの基底クラス
 */
#pragma once


namespace nsApp {
    namespace nsActor {
        /**
         * アクタークラス
         * 見た目を持つゲームオブジェクトの基底クラス
         */
        class Actor : public IGameObject
        {
        public:
            /**
             * トランスフォーム(座標(position)、拡縮(scale)、回転(rotation))
　　　　　　 * NOTE:位置や回転などの変換情報を管理する
             *      例外としてpublicにしているのは、頻繁にアクセスされるため
             */
            std::shared_ptr<nsApp::Transform> m_transform;


        /**
         *  NOTE:本クラスで作成した変数は、派生クラスで関数越しにアクセスせず、直接変数にアクセスしてもよい
         */ 
        protected:  
            /** モデル描画 */
            ModelRender m_modelRender;
        

        public:
            Actor();
            virtual ~Actor();


        public:
            virtual bool Start() override;
            virtual void Update() override;
            virtual void Render(RenderContext& rc) override; 
        };
    }
}
