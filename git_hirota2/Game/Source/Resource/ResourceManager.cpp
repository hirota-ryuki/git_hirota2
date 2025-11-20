#include "stdafx.h"
#include "ResourceManager.h"


namespace nsApp {
    /** シングルトンインスタンスの初期化。 */
    ResourceManager* ResourceManager::m_instance = nullptr;


    ResourceManager::ResourceManager()
    {
    }


    ResourceManager::~ResourceManager()
    {
    }
}
