//STD
#include <cassert>
#include <iostream>

namespace zge
{

template <class ResourceType>
std::unique_ptr<ResourceManager<ResourceType>> ResourceManager<ResourceType>::m_instance;

template <class ResourceType>
ResourceManager<ResourceType>::~ResourceManager()
{
    std::cout << "[ResourceManager] Destructor\n";

    //assert("[ResourceManager::~ResourceManager] Not all resources have been destructed" && m_resources.size() == 0); //There should be nothing left in the map as all resources are destroyed when ref count hits 0
    std::cout << "[ResourceManager] " << m_resources.size() << " Resources Unaccounted for:\n";

    for (auto it = m_resources.begin(); it != m_resources.end(); it++)
    {
        std::cout << "[" << typeid(ResourceType).name() << "] " << it->first << " @ " << it->second.first << "\n";
    }
}

template <class ResourceType>
ResourceManager<ResourceType>& ResourceManager<ResourceType>::getInstance()
{
    if (m_instance == nullptr)
    {
        std::cout << "[ResourceManager] Constructed\n";
        m_instance = std::unique_ptr<ResourceManager<ResourceType>>(new ResourceManager<ResourceType>);
    }

    return *m_instance.get();
}

template <class ResourceType>
bool ResourceManager<ResourceType>::create(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    if (m_resources.count(name) == 0)
    {
        //std::cout << "[ResourceManager] Creating " << name << "\n";
        m_resources[name].first = 1;
        m_resources[name].second.reset(new ResourceType());
        return true;
    }
    else
    {
        m_resources[name].first++;
        //std::cout << "[ResourceManager] Increased ref count of " << name << " to " << m_resources[name].first << "\n";
    }

    return false;
}

template <class ResourceType>
void ResourceManager<ResourceType>::destroy(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto it = m_resources.find(name);
    if (it == m_resources.end())
    {
        std::cout << "[ResourceManager] Cannot find the resource " << name << " to destroy\n";
        return;
    }

    if (it->second.first == 1)
    {
        //std::cout << "[ResourceManager] Erasing " << name << "\n";
        m_resources.erase(it);
    }
    else if (it->second.first > 1)
    {
        it->second.first--;
        //std::cout << "[ResourceManager] Decreased ref count of " << name << " to " << it->second.first << "\n";
    }
    else
    {
        assert(!"[ResourceManager] There are no references to this resource\n");
    }
}

template <class ResourceType>
ResourceType& ResourceManager<ResourceType>::get(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    assert("[ResourceManager::get()] resource does not exist" && m_resources.count(name)); //Resource exists

    return *m_resources[name].second.get();
}

} //ZGE
