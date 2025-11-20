/**
 * リソースマネージャークラス
 */
#pragma once


namespace nsApp {
    /**
     * リソースマネージャークラス
     */
    class ResourceManager
    {
    private:
        /** パス情報を管理する連想配列 */
        std::unordered_map<std::string, std::string> m_paths;
        /** 基準となるパス */
        std::string m_basePath;


    private:
        ResourceManager();
        ~ResourceManager();


    public:
        /** シングルトンインスタンスを生成する */
        static void CreateInstance()
        {
            /** 警告: インスタンスが既に生成されている場合は、例外を投げる */
            K2_ASSERT(m_instance == nullptr, "ResourceManager instance is created yet.");
            // インスタンスを生成する。
            m_instance = new ResourceManager();
        }


        /** シングルトンインスタンスを取得する */
        static ResourceManager* GetInstance() {
            /** 警告: インスタンスが生成されていない場合は、例外を投げる */
            K2_ASSERT(m_instance != nullptr, "ResourceManager instance is not created yet. Call CreateInstance() first.");
            /** インスタンスを取得する */
            return m_instance;
        }


        /** シングルトンインスタンスを解放する */
        static void ReleaseInstance()
        {
            /** インスタンスを開放する */
            delete m_instance;
            m_instance = nullptr;
        }


    public:
        /** シングルトンインスタンス本体 */
        static ResourceManager* m_instance;
    };
}
