#include "Asteroid.hpp"

Asteroid::Asteroid(sf::Vector2f pos, unsigned sides, float speed, sf::Vector2f windowSize):
Collider(sides),
m_velocity(1, 1),
m_speed(speed),
m_isAlive(true),
m_wasOnScreen(false),
m_explosionSound("audio/explosion.wav")
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

    sf::Vector2f targetPos(std::rand() % int(windowSize.x),
                          std::rand() % int(windowSize.y));

    zge::Vector targetDirection(targetPos.x - pos.x,
                                targetPos.y - pos.y);
    m_velocity *= targetDirection.normalized();
    m_velocity *= m_speed;
    m_velocity /= sides;

    m_rotationSpeed = (std::rand() % int((speed*2)/sides)) - speed/sides;

    m_collisionShape.setFillColor(sf::Color(0, 255, 255, 100));
}

void Asteroid::handleEvent(const sf::Event& event)
{

}

void Asteroid::update(float dt, sf::RenderWindow& window)
{
    m_shape.rotate(m_rotationSpeed * dt);

    if (m_wasOnScreen)
    {
        m_shape.move(m_velocity.x * dt, m_velocity.y * dt);
    }
    else
    {
        m_shape.move(m_velocity.x * dt * 10, m_velocity.y * dt * 10);
    }

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
    m_explosionSound->play();
}

bool Asteroid::isAlive()
{
    return m_isAlive;
}

bool Asteroid::canSplit()
{
    return (m_shape.getPointCount() - 2 >= 5);
}

Asteroid Asteroid::split(sf::Vector2f windowSize)
{
    if (canSplit())
    {
        std::cout << "Splitting Asteroid\n";
        Asteroid a(sf::Vector2f(m_shape.getPosition().x + (std::rand() % 20 - 10),
                                m_shape.getPosition().y + (std::rand() % 20 - 10)),
                   m_shape.getPointCount() - 2,
                   m_speed + (std::rand() % 200 + 50),
                   windowSize
                   );
        return a;
    }
    else
    {
        std::cout << "This should not happen\n";
        Asteroid a(m_shape.getPosition(), 5, m_speed, windowSize);
        return a;
    }
}

void Asteroid::keepInWindow(sf::RenderWindow& window)
{
    if (m_shape.getPosition().x + m_radius <= 0)
    {
        if (m_wasOnScreen)
        {
            m_shape.setPosition(window.getView().getSize().x + m_radius, m_shape.getPosition().y);
        }
    }
    else if (m_shape.getPosition().x - m_radius >= window.getView().getSize().x)
    {
        if (m_wasOnScreen)
        {
            m_shape.setPosition(-m_radius, m_shape.getPosition().y);
        }
    }
    else if (m_shape.getPosition().y + m_radius <= 0)
    {
        if (m_wasOnScreen)
        {
            m_shape.setPosition(m_shape.getPosition().x, window.getView().getSize().y + m_radius);
        }
    }
    else if (m_shape.getPosition().y - m_radius >= window.getView().getSize().y)
    {
        if (m_wasOnScreen)
        {
            m_shape.setPosition(m_shape.getPosition().x, -m_radius);
        }
    }
    else if (!m_wasOnScreen)
    {
        m_wasOnScreen = true;
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

