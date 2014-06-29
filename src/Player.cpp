#include "Player.hpp"

//STD
#include <cmath>

//3RD

//SELF
#include "ZGE/Utility.hpp"

Player::Player():
m_Texture("textures/ship.png"),
m_Acceleration(200),
m_MaxVelocityLength(m_Acceleration * 2)
{
    m_Texture.get().setSmooth(true);

    m_Sprite.setTexture(m_Texture.get());

    m_Sprite.setOrigin(m_Texture.get().getSize().x / 2,
                       m_Texture.get().getSize().y / 2);

    m_Sprite.setPosition(1280/2, 720/2);

    useWASD();
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

    if (m_Gravity.length() != 0)
    {
        m_Velocity += m_Gravity * (1/m_Gravity.length()) * (m_Acceleration * dt.asSeconds() * 0.8);
    }
    m_Sprite.move(m_Velocity.x * dt.asSeconds(), m_Velocity.y * dt.asSeconds());

    if (m_Sprite.getPosition().x + (m_Texture.get().getSize().x / 2) <= 0)
    {
        m_Sprite.setPosition(1280, m_Sprite.getPosition().y);
    }
    else if (m_Sprite.getPosition().x - (m_Texture.get().getSize().x / 2) >= 1280)
    {
        m_Sprite.setPosition(0, m_Sprite.getPosition().y);
    }
    else if (m_Sprite.getPosition().y + (m_Texture.get().getSize().y / 2 ) <= 0)
    {
        m_Sprite.setPosition(m_Sprite.getPosition().x, 720);
    }
    else if (m_Sprite.getPosition().y - (m_Texture.get().getSize().y / 2) >= 720)
    {
        m_Sprite.setPosition(m_Sprite.getPosition().x, 0);
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite, states);
    zge::drawLine(target, m_Sprite.getPosition().x, m_Sprite.getPosition().y, m_Sprite.getPosition().x + m_Velocity.x, m_Sprite.getPosition().y + m_Velocity.y, sf::Color::Red);
}

void Player::useWASD()
{
    m_forwards = sf::Keyboard::Key::W;
    m_backwards = sf::Keyboard::Key::S;
    m_left = sf::Keyboard::Key::A;
    m_right = sf::Keyboard::Key::D;
    m_decelerate = sf::Keyboard::Key::LShift;
    m_shoot = sf::Keyboard::Key::Space;
}

void Player::useArrow()
{
    m_forwards = sf::Keyboard::Key::Up;
    m_backwards = sf::Keyboard::Key::Down;
    m_left = sf::Keyboard::Key::Left;
    m_right = sf::Keyboard::Key::Right;
    m_decelerate = sf::Keyboard::Key::RShift;
    m_shoot = sf::Keyboard::Key::RControl;
}

void Player::setColor(sf::Color c)
{
    m_Sprite.setColor(c);
}

void Player::setGravityPosition(zge::Vector pos)
{
    m_Gravity = (zge::Vector(pos.x, pos.y) - zge::Vector(m_Sprite.getPosition().x, m_Sprite.getPosition().y));
}

zge::Vector Player::getPosition()
{
    return zge::Vector(m_Sprite.getPosition().x, m_Sprite.getPosition().y);
}
