/*
*
*
* sf::Sound specialization
*
*
*/
#include "ZGE/ResourceManagement/Resource.hpp"

namespace zge
{

unsigned int Resource<sf::Sound>::m_globalSoundInstances;

Resource<sf::Sound>::Resource(std::string n)
    : m_name(n)
{
    std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);

    //std::cout << "[Resource] Constructor | " << m_name << "\n";
    m_globalSoundInstances++;

    assert("There are more than 256 sound instances, this may be close to OpenAL's limit" && m_globalSoundInstances < 256);

    if (ResourceManager<sf::SoundBuffer>::getInstance().create(m_name))
    {
        assert("[Resource<sf::Sound>::Resource] Could not load sf::SoundBuffer from file" && ResourceManager<sf::SoundBuffer>::getInstance().get(m_name).loadFromFile(m_name));
    }

    m_sound.setBuffer(ResourceManager<sf::SoundBuffer>::getInstance().get(m_name));
}

Resource<sf::Sound>::~Resource()
{
    //std::cout << "[Resource] Destructor | " << m_name << "\n";
    //std::cout << "\t[Resource] Global Sound Instances = " << m_globalSoundInstances << "\n";
    m_globalSoundInstances--;
    ResourceManager<sf::SoundBuffer>::getInstance().destroy(m_name);
}

Resource<sf::Sound>::Resource(const Resource<sf::Sound>& res)
{
    this->copyResource(res);
}

Resource<sf::Sound>& Resource<sf::Sound>::operator=(const Resource<sf::Sound>& res)
{
    this->copyResource(res);
    return *this;
}

sf::Sound& Resource<sf::Sound>::get()
{
    return m_sound;
}

void Resource<sf::Sound>::copyResource(const Resource<sf::Sound>& res)
{
    //std::cout << "[Resource] Copied\n";
    //std::cout << "\tthis = " << m_name << "\n\tother = " << res.m_name << "\n";

    if (!m_name.empty())
    {
        ResourceManager<sf::SoundBuffer>::getInstance().destroy(m_name); //Destroy whatever resource res was holding before
        m_globalSoundInstances--;
    }

    m_name = res.m_name;
    m_sound = res.m_sound;
    ResourceManager<sf::SoundBuffer>::getInstance().create(m_name); //Increase reference count
    m_globalSoundInstances++;
}

/*
*
*
* sf::Music specialization
*
*
*/
#include "ZGE/ResourceManagement/Resource.hpp"

unsigned int Resource<sf::Music>::m_globalMusicInstances;

Resource<sf::Music>::Resource(std::string n)
    : m_name(n)
{
    std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);

    //std::cout << "[Resource] Constructor | " << m_name << "\n";
    m_globalMusicInstances++;

    assert(m_globalMusicInstances < 256);

    m_music.openFromFile(m_name);
}

Resource<sf::Music>::~Resource()
{
    //std::cout << "[Resource] Destructor | " << m_name << "\n";
    //std::cout << "\t[Resource] Global Music Instances = " << m_globalMusicInstances << "\n";
    m_globalMusicInstances--;
}

sf::Music& Resource<sf::Music>::get()
{
    return m_music;
}

} //ZGE
