#include "Asteroid.hpp"

Asteroid::Asteroid(sf::Vector2f pos, unsigned sides, float speed):
Collider(sides),
m_velocity(1, 1),
m_speed(speed),
m_isAlive(true)
{
    if (sides < 5)
    {
        sides = 5;
    }

    m_radius = (sides - 4) * 8;

    m_shape.setPosition(pos);
    m_shape.setOutlineThickness(1.5f);
    m_shape.setOutlineColor(sf::Color::Black);

    createShape(sides);

    int angle = std::rand() % 360;
    m_velocity *= zge::Vector::degToVector(angle);
    m_velocity *= m_speed;
    m_velocity /= sides;
    //std::cout << m_velocity.x << ", " << m_velocity.y << "\n";
    //std::cout << "ang = " << angle << "\n";

    m_rotationSpeed = (std::rand() % int((speed*2)/sides)) - speed/sides;

    m_collisionShape.setFillColor(sf::Color(0, 255, 255, 100));
}

void Asteroid::handleEvent(const sf::Event& event)
{

}

void Asteroid::update(float dt, sf::RenderWindow& window)
{
    m_shape.rotate(m_rotationSpeed * dt);
    m_shape.move(m_velocity.x * dt, m_velocity.y * dt);

    keepInWindow(window);

    updateCollisionShape(m_shape.getPosition(),
                         m_radius,
                         m_shape.getRotation());
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

void Asteroid::handleCollision(sf::CircleShape otherColShape)
{
    m_isAlive = false;
    m_isColliding = true;
}

bool Asteroid::isAlive()
{
    return m_isAlive;
}

bool Asteroid::canSplit()
{
    return (m_shape.getPointCount() - 2 >= 5);
}

Asteroid Asteroid::split()
{
    if (canSplit())
    {
        std::cout << "Splitting Asteroid\n";
        Asteroid a(sf::Vector2f(m_shape.getPosition().x + (std::rand() % 20 - 10), m_shape.getPosition().y + (std::rand() % 20 - 10)),
                                                            m_shape.getPointCount() - 2,
                                                            m_speed + (std::rand() % 200 + 50));
        return a;
    }
    else
    {
        std::cout << "This should not happen\n";
        Asteroid a(m_shape.getPosition(), 5, m_speed);
        return a;
    }
}

void Asteroid::keepInWindow(sf::RenderWindow& window)
{
    if (m_shape.getPosition().x + m_radius <= 0)
    {
        m_shape.setPosition(window.getView().getSize().x + m_radius, m_shape.getPosition().y);
    }
    else if (m_shape.getPosition().x - m_radius >= window.getView().getSize().x)
    {
        m_shape.setPosition(-m_radius, m_shape.getPosition().y);
    }
    else if (m_shape.getPosition().y + m_radius <= 0)
    {
        m_shape.setPosition(m_shape.getPosition().x, window.getView().getSize().y + m_radius);
    }
    else if (m_shape.getPosition().y - m_radius >= window.getView().getSize().y)
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

