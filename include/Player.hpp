#ifndef PLAYER_HPP
#define PLAYER_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>
#include <ZGE/Vector.hpp>

//SELF

class Player : public sf::Drawable
{
public:
    Player();

    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void useWASD();
    void useArrow();

    void setColor(sf::Color c);
    void setGravityPosition(zge::Vector pos);

    zge::Vector getPosition();

private:
    sf::Sprite m_sprite;
    zge::Resource<sf::Texture> m_texture;

    float m_acceleration;
    zge::Vector m_velocity;
    float m_maxVelocityLength;

    sf::Keyboard::Key m_forwards;
    sf::Keyboard::Key m_backwards;
    sf::Keyboard::Key m_left;
    sf::Keyboard::Key m_right;
    sf::Keyboard::Key m_decelerate;
    sf::Keyboard::Key m_shoot;
};

#endif //PLAYER_HPP
