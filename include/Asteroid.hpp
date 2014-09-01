#ifndef ASTEROID_HPP
#define ASTEROID_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/Vector.hpp>
#include <ZGE/Collider.hpp>

//SELF

class Asteroid : public sf::Drawable, public zge::Collider
{

public:
    Asteroid(sf::Vector2f pos, unsigned sides, float speed);

    void handleEvent(const sf::Event& event);
    void update(float dt, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void handleCollision(sf::CircleShape otherColShape) override;
    bool isAlive();

    bool canSplit();
    Asteroid split();

private:
    void keepInWindow(sf::RenderWindow& window);
    void createShape(unsigned sides);

    mutable sf::ConvexShape m_shape;
    zge::Vector m_velocity;
    float m_radius;
    float m_speed;
    float m_rotationSpeed;
    mutable bool m_isColliding;
    bool m_isAlive;
};

#endif //ASTEROID_HPP
