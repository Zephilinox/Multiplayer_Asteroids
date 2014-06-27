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

    void handleEvent(const sf::Event);
    void update(const sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite m_Sprite;
    zge::Resource<sf::Texture> m_Texture;

    float m_Acceleration;
    zge::Vector m_Velocity;
    float m_MaxVelocityLength;
};

#endif //PLAYER_HPP
