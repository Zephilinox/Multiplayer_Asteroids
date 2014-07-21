#ifndef BULLET_HPP
#define BULLET_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/Vector.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>

//SELF
#include "Collider.hpp"

class Bullet : public sf::Drawable, public Collider
{
public:
    Bullet(sf::Vector2f pos, float rotation, float speed, sf::Color col);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void handleCollision(sf::CircleShape otherColShape) override;

    sf::Color getColor();
    unsigned getWarpCount();
    float getScore();

    bool isAlive();

private:
    void keepInWindow();

    zge::Resource<sf::Texture> m_texture;
    mutable sf::Sprite m_sprite;

    float m_speed;
    zge::Vector m_velocity;

    unsigned m_warpCount;

    mutable bool m_isColliding;
    bool m_isAlive;

    float m_score;
};

#endif //BULLET_HPP
