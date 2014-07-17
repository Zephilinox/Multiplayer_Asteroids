#ifndef KEYBINDINGCACHE_HPP
#define KEYBINDINGCACHE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF

class KeybindingCache
{
public:
    KeybindingCache();

   sf::Keyboard::Key get(std::string name);
    void add(std::string name, sf::Keyboard::Key key);
    void remove(std::string name);
    void removeAll();

private:
    std::map<std::string, sf::Keyboard::Key> m_keybindings;
};

#endif //KEYBINDINGCACHE_HPP
