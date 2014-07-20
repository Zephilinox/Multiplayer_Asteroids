#include "Asteroid.hpp"

Asteroid::Asteroid(sf::Vector2f pos, unsigned sides, float speed):
m_velocity(1, 1),
m_speed(speed)
{
    if (sides < 5)
    {
        sides = 5;
    }

    m_radius = (sides - 4) * 8;

    m_shape.setPosition(pos);

    createShape(sides);

    int angle = std::rand() % 360;
    m_velocity *= zge::Vector::degToVector(angle);
    m_velocity *= m_speed;
    m_velocity /= sides;
    std::cout << m_velocity.x << ", " << m_velocity.y << "\n";
    //std::cout << "ang = " << angle << "\n";

    m_rotationSpeed = (std::rand() % int((speed*2)/sides)) - speed/sides;
}

void Asteroid::handleEvent(const sf::Event& event)
{

}

void Asteroid::update(float dt)
{
    m_shape.rotate(m_rotationSpeed * dt);
    m_shape.move(m_velocity.x * dt, m_velocity.y * dt);

    keepInWindow();
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

void Asteroid::keepInWindow()
{
    if (m_shape.getPosition().x + m_radius <= 0)
    {
        m_shape.setPosition(1280 + m_radius, m_shape.getPosition().y);
    }
    else if (m_shape.getPosition().x - m_radius >= 1280)
    {
        m_shape.setPosition(-m_radius, m_shape.getPosition().y);
    }
    else if (m_shape.getPosition().y + m_radius <= 0)
    {
        m_shape.setPosition(m_shape.getPosition().x, 720 + m_radius);
    }
    else if (m_shape.getPosition().y - m_radius >= 720)
    {
        m_shape.setPosition(m_shape.getPosition().x, -m_radius);
    }
}

void Asteroid::createShape(unsigned sides)
{
    float totalAngle = (sides - 2) * 180;
    float interiorAngle = totalAngle / sides;
    float exteriorAngle = 180 - interiorAngle;
    m_shape.setPointCount(sides);

    for (unsigned i = 0; i < sides; ++i)
    {
        zge::Vector angleDir = zge::Vector::degToVector(exteriorAngle * i);
        m_shape.setPoint(i, sf::Vector2f(angleDir.x, angleDir.y) * m_radius);
        //std::cout << angleDir.x * m_radius << ", " << angleDir.y * m_radius << "\n";
    }
}
