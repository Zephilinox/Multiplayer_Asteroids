#include "Player.hpp"

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
}

void Player::handleEvent(const sf::Event)
{

}

void Player::update(const sf::Time dt)
{
    double shipRadian = zge::degToRad(m_Sprite.getRotation());
    double sinRadian = std::sin(shipRadian);
    double cosRadian = std::cos(shipRadian);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_Velocity.x += m_Acceleration * sinRadian * dt.asSeconds();
        m_Velocity.y += -1 * m_Acceleration * cosRadian * dt.asSeconds();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_Velocity.x += -1 * m_Acceleration * sinRadian * dt.asSeconds();
        m_Velocity.y += m_Acceleration * cosRadian * dt.asSeconds();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_Sprite.rotate(-300 * dt.asSeconds());
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_Sprite.rotate(300 * dt.asSeconds());
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
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

    m_Sprite.move(m_Velocity.x * dt.asSeconds(), m_Velocity.y * dt.asSeconds());
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite, states);
}
