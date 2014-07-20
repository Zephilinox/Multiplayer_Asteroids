#ifndef ASTEROID_HPP
#define ASTEROID_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/Vector.hpp>

//SELF

class Asteroid : public sf::Drawable
{

public:
    Asteroid(sf::Vector2f pos, unsigned sides, float speed);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void keepInWindow();
    void createShape(unsigned sides);

    sf::ConvexShape m_shape;
    zge::Vector m_velocity;
    float m_radius;
    float m_speed;
    float m_rotationSpeed;
};

#endif //ASTEROID_HPP
