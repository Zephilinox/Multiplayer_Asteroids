#include "Player.hpp"

//STD
#include <cmath>

//3RD

//SELF
#include "Utility.hpp"

Player::Player():
m_Texture("textures/ship.png"),
m_Acceleration(300),
m_MaxVelocityLength(m_Acceleration * 2)
{
    m_Texture.get().setSmooth(true);

    m_Sprite.setTexture(m_Texture.get());

    m_Sprite.setOrigin(m_Texture.get().getSize().x / 2,
                       m_Texture.get().getSize().y / 2);

    m_Sprite.setPosition(50, 50);

    m_forwards = sf::Keyboard::Key::W;
    m_backwards = sf::Keyboard::Key::S;
    m_left = sf::Keyboard::Key::A;
    m_right = sf::Keyboard::Key::D;
    m_decelerate = sf::Keyboard::Key::LShift;
    m_shoot = sf::Keyboard::Key::Space;
}

void Player::handleEvent(const sf::Event)
{

}

void Player::update(const sf::Time dt)
{
    double shipRadian = zge::degToRad(m_Sprite.getRotation());
    double sinRadian = std::sin(shipRadian);
    double cosRadian = std::cos(shipRadian);

    if (sf::Keyboard::isKeyPressed(m_forwards))
    {
        m_Velocity.x += m_Acceleration * sinRadian * dt.asSeconds();
        m_Velocity.y += -1 * m_Acceleration * cosRadian * dt.asSeconds();
    }

    if (sf::Keyboard::isKeyPressed(m_backwards))
    {
        m_Velocity.x += -1 * m_Acceleration * sinRadian * dt.asSeconds();
        m_Velocity.y += m_Acceleration * cosRadian * dt.asSeconds();
    }

    if (sf::Keyboard::isKeyPressed(m_left))
    {
        m_Sprite.rotate(-300 * dt.asSeconds());
    }

    if (sf::Keyboard::isKeyPressed(m_right))
    {
        m_Sprite.rotate(300 * dt.asSeconds());
    }

    if (sf::Keyboard::isKeyPressed(m_decelerate))
    {
        if (m_Velocity.length() > 5)
        {
            m_Velocity.x -= m_Acceleration * m_Velocity.normalized().x * dt.asSeconds();
            m_Velocity.y -= m_Acceleration * m_Velocity.normalized().y * dt.asSeconds();
        }
        else
        {
            m_Velocity.x = 0;
            m_Velocity.y = 0;
        }
    }

    if (m_Velocity.length() > m_MaxVelocityLength)
    {
        m_Velocity *= m_MaxVelocityLength / m_Velocity.length();
    }

    zge::Vector gravity = (zge::Vector(1280/2, 720/2) - zge::Vector(m_Sprite.getPosition().x, m_Sprite.getPosition().y));
    float gravityMultiplier = std::min(1/gravity.length() * 20, 10.d);

    gravity *= gravityMultiplier;

    m_Velocity += gravity;

    m_Sprite.move(m_Velocity.x * dt.asSeconds(), m_Velocity.y * dt.asSeconds());
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    utility::drawLine(target, m_Sprite.getPosition().x, m_Sprite.getPosition().y, m_Sprite.getPosition().x + m_Velocity.x, m_Sprite.getPosition().y + m_Velocity.y, sf::Color::Red);
    utility::drawLine(target, m_Sprite.getPosition().x, m_Sprite.getPosition().y, 1280/2, 720/2, sf::Color::Blue);
    target.draw(m_Sprite, states);
}
