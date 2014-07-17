#include "KeybindingCache.hpp"

//STD
#include <cassert>

//3RD

//SELF

KeybindingCache::KeybindingCache()
{
}

sf::Keyboard::Key KeybindingCache::get(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    assert(m_keybindings.count(name));
    return m_keybindings[name];
}

void KeybindingCache::add(std::string name, sf::Keyboard::Key key)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    m_keybindings[name] = key;
}

void KeybindingCache::remove(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto it = m_keybindings.find(name);
    assert(it != m_keybindings.end());
    m_keybindings.erase(it);
}

void KeybindingCache::removeAll()
{
    m_keybindings.clear();
}
