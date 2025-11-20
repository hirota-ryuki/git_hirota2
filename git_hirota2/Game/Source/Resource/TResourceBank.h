/**
 * リソースを管理するバンククラス
 */
#pragma once
#include "Source/Engine/Noncopyable/Noncopyable.h"
#include <memory>


namespace nsEngine {
    /**
     * リソースクラス
     */
    template<class TResource>
    class TResourceBank : public Noncopyable{
    private:
        /** リソースを格納するマップの名前 */
        using TResourcePtr = std::unique_ptr<TResource>;
        /** ファイルパスをキーにしてリソースを格納するマップ */
        std::map<std::string, TResourcePtr> m_resourceMap;


    public:
        /** リソースを指定して呼び出す */
        TResource* Get(const char* filepath) {
            /** ファイルパスをキーにしてリソースを取得する */
            /** リソースが登録されていない場合はend()を返す */
            auto it = m_resourceMap.find(filepath);
            if (it != m_resourceMap.end()) {
                /** バンクに登録されているため、ファイルパスを返す */
                /** std::map<first, second>　firstはキー、secondは値 */
                return it->second.get();
            }
            return nullptr;
        }


        /** リソースを登録する */
        void Regist(const char* filePath, TResource* resource)
        {
            auto it = m_resourceMap.find(filePath);
            /** 未登録の場合 */
            if (it == m_resourceMap.end()) {             
                m_resourceMap.insert(
                    //std::pair< std::string, TResourcePtr>(filePath, resource)
                    std::make_pair(filePath, TResourcePtr(resource))
                );
            }
        }
    };
}
