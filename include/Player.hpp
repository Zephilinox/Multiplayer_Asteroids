#ifndef PLAYER_HPP
#define PLAYER_HPP

//STD
#include <vector>

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>
#include <ZGE/Vector.hpp>

//SELF
#include "KeybindingCache.hpp"
#include "Bullet.hpp"

class Player : public sf::Drawable
{
public:
    Player(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void useWASD();
    void useArrow();

    void setColor(sf::Color c);
    void setGravityPosition(zge::Vector pos);

    zge::Vector getPosition();

private:
    void movement(float dt);
    void capVelocity();
    void keepInWindow();

    sf::RenderWindow& m_window;
    sf::Sprite m_sprite;
    zge::Resource<sf::Texture> m_texture;

    float m_acceleration;
    zge::Vector m_velocity;
    float m_maxVelocityLength;

    KeybindingCache m_keys;

    std::vector<Bullet> m_bullets;
};

#endif //PLAYER_HPP
