#ifndef RESOURCE_HPP
#define RESOURCE_HPP

//STD
#include <string>
#include <memory>

//3RD
#include <SFML/Audio.hpp>

//SELF
#include "ResourceManager.hpp"

namespace zge
{

template <class ResourceType>
class Resource
{
public:
    Resource(std::string n);
    ~Resource();

    Resource(const Resource& res);
    Resource& operator=(const Resource& res);
    operator ResourceType&() const;
    ResourceType* operator->();

    ResourceType& get();

private:
    void copyResource(const Resource<ResourceType>& res);

    std::string m_name;
};

/*
*
*
* sf::Sound specialization
*
*
*/
template <>
class Resource<sf::Sound>
{
public:
    Resource(std::string n);
    ~Resource();

    Resource(const Resource<sf::Sound>& res);
    Resource<sf::Sound>& operator=(const Resource<sf::Sound>& res);

    sf::Sound& get();

private:
    void copyResource(const Resource<sf::Sound>& res);

    std::string m_name;
    sf::Sound m_sound;
    static unsigned int m_globalSoundInstances;
};

/*
*
*
* sf::Music specialization
*
*
*/
template <>
class Resource<sf::Music>
{
public:
    Resource(const Resource<sf::Music>& res) = delete;
    Resource<sf::Music>& operator=(const Resource<sf::Music>& res) = delete;

    Resource(std::string n);
    ~Resource();

    sf::Music& get();

private:
    std::string m_name;
    sf::Music m_music;
    static unsigned int m_globalMusicInstances;
};

} //ZGE

#include "ZGE/ResourceManagement/Resource.inl"

#endif //RESOURCE_HPP
