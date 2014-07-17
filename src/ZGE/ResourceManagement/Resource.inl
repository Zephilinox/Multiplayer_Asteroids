//STD
#include <algorithm>
#include <locale>

namespace zge
{

template <class ResourceType>
Resource<ResourceType>::Resource(std::string n)
    : m_name(n)
{
    std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);

    //std::cout << "[Resource] Constructor | " << m_name << "\n";
    if (ResourceManager<ResourceType>::getInstance().create(m_name))
    {
        assert(ResourceManager<ResourceType>::getInstance().get(m_name).loadFromFile(m_name));
    }
}

template <class ResourceType>
Resource<ResourceType>::~Resource()
{
    //std::cout << "[Resource] Destructor | " << m_name << "\n";
    ResourceManager<ResourceType>::getInstance().destroy(m_name);
}

template <class ResourceType>
Resource<ResourceType>::Resource(const Resource<ResourceType>& res)
{
    this->copyResource(res);
}

template <class ResourceType>
Resource<ResourceType>& Resource<ResourceType>::operator=(const Resource<ResourceType>& res)
{
    this->copyResource(res);
    return *this;
}

template <class ResourceType>
Resource<ResourceType>::operator ResourceType&() const
{
    return ResourceManager<ResourceType>::getInstance().get(m_name);
}

template <class ResourceType>
ResourceType* Resource<ResourceType>::operator->()
{
    return &get();
}

template <class ResourceType>
ResourceType& Resource<ResourceType>::get()
{
    return ResourceManager<ResourceType>::getInstance().get(m_name);
}

template <class ResourceType>
void Resource<ResourceType>::copyResource(const Resource<ResourceType>& res)
{
    //std::cout << "[Resource] Copied\n";
    //std::cout << "\tthis = " << m_name << "\n\tother = " << res.m_name << "\n";

    if (!m_name.empty())
    {
        ResourceManager<ResourceType>::getInstance().destroy(m_name); //Destroy whatever resource res was holding before
    }

    m_name = res.m_name;
    ResourceManager<ResourceType>::getInstance().create(m_name); //Increase reference count
}

} //ZGE
