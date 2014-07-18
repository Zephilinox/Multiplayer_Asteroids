#ifndef BULLET_HPP
#define BULLET_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/Vector.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>

//SELF

class Bullet : public sf::Drawable
{
public:
    Bullet(sf::Vector2f pos, float rotation, float speed);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    zge::Resource<sf::Texture> m_texture;
    sf::Sprite m_sprite;

    float m_speed;
    zge::Vector m_velocity;
};

#endif //BULLET_HPP
