#pragma once
class FilePathManager
{
private:
    FilePathManager() {};
    ~FilePathManager() {};
public:
    static void CreateInstance()
    {
        //�x���B
        K2_ASSERT(m_instance == nullptr, "FilePathManager instance is created yet.");
        m_instance = new FilePathManager();

    }

    static FilePathManager* GetInstance() {
        K2_ASSERT(m_instance != nullptr, "FilePathManager instance is not created yet. Call CreateInstance() first.");
        return m_instance;
    }

    static void ReleaseInstance()
    {
        delete m_instance;
        m_instance = nullptr;
    }

    static FilePathManager* m_instance;
    std::unordered_map<std::string, std::string> m_paths;
    std::string m_basePath;
public:

};

