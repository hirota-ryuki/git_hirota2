#pragma once
class FilePathManager
{
private:
    FilePathManager() {};
    ~FilePathManager() {};
public:
    /// <summary>
    /// シングルトンインスタンスを生成する。
    /// </summary>
    static void CreateInstance()
    {
        //警告: インスタンスが既に生成されている場合は、例外を投げる。
        K2_ASSERT(m_instance == nullptr, "FilePathManager instance is created yet.");
        // インスタンスを生成する。
        m_instance = new FilePathManager();
    }

    /// <summary>
    /// シングルトンインスタンスを取得する。
    /// </summary>
    static FilePathManager* GetInstance() {
        //警告: インスタンスが生成されていない場合は、例外を投げる。
        K2_ASSERT(m_instance != nullptr, "FilePathManager instance is not created yet. Call CreateInstance() first.");
        // インスタンスを取得する。
        return m_instance;
    }

    /// <summary>
    /// シングルトンインスタンスを解放する。
    /// </summary>
    static void ReleaseInstance()
    {
        // インスタンスを解放する。
        delete m_instance;
        m_instance = nullptr;
    }

public:
    static FilePathManager*                      m_instance; // シングルトンインスタンス本体。
private:
    std::unordered_map<std::string, std::string> m_paths;    // 複数のパス情報を管理する連想配列。
    std::string                                  m_basePath; // 基準となるパス。
};

