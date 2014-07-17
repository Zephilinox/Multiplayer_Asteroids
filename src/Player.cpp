#include "Player.hpp"

//STD
#include <cmath>

//3RD

//SELF
#include "ZGE/Utility.hpp"

Player::Player():
m_texture("textures/ship.png"),
m_acceleration(200),
m_maxVelocityLength(m_acceleration * 2)
{
    m_texture.get().setSmooth(true);

    m_sprite.setTexture(m_texture.get());

    m_sprite.setOrigin(m_texture.get().getSize().x / 2,
                       m_texture.get().getSize().y / 2);

    m_sprite.setPosition(1280/2, 720/2);

    useWASD();
}

void Player::handleEvent(const sf::Event& event)
{

}

void Player::update(float dt)
{
    double shipRadian = zge::degToRad(m_sprite.getRotation());
    double sinRadian = std::sin(shipRadian);
    double cosRadian = std::cos(shipRadian);

    if (sf::Keyboard::isKeyPressed(m_forwards))
    {
        m_velocity.x += m_acceleration * sinRadian * dt;
        m_velocity.y += -1 * m_acceleration * cosRadian * dt;
    }

    if (sf::Keyboard::isKeyPressed(m_backwards))
    {
        m_velocity.x += -1 * m_acceleration * sinRadian * dt;
        m_velocity.y += m_acceleration * cosRadian * dt;
    }

    if (sf::Keyboard::isKeyPressed(m_left))
    {
        m_sprite.rotate(-300 * dt);
    }

    if (sf::Keyboard::isKeyPressed(m_right))
    {
        m_sprite.rotate(300 * dt);
    }

    if (sf::Keyboard::isKeyPressed(m_decelerate))
    {
        if (m_velocity.length() > 5)
        {
            m_velocity.x -= m_acceleration * m_velocity.normalized().x * dt;
            m_velocity.y -= m_acceleration * m_velocity.normalized().y * dt;
        }
        else
        {
            m_velocity.x = 0;
            m_velocity.y = 0;
        }
    }

    if (m_velocity.length() > m_maxVelocityLength)
    {
        m_velocity *= m_maxVelocityLength / m_velocity.length();
    }

    m_sprite.move(m_velocity.x * dt, m_velocity.y * dt);

    if (m_sprite.getPosition().x + (m_texture.get().getSize().x / 2) <= 0)
    {
        m_sprite.setPosition(1280, m_sprite.getPosition().y);
    }
    else if (m_sprite.getPosition().x - (m_texture.get().getSize().x / 2) >= 1280)
    {
        m_sprite.setPosition(0, m_sprite.getPosition().y);
    }
    else if (m_sprite.getPosition().y + (m_texture.get().getSize().y / 2 ) <= 0)
    {
        m_sprite.setPosition(m_sprite.getPosition().x, 720);
    }
    else if (m_sprite.getPosition().y - (m_texture.get().getSize().y / 2) >= 720)
    {
        m_sprite.setPosition(m_sprite.getPosition().x, 0);
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
    zge::drawLine(target, m_sprite.getPosition().x, m_sprite.getPosition().y, m_sprite.getPosition().x + m_velocity.x, m_sprite.getPosition().y + m_velocity.y, sf::Color::Red);
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
    m_sprite.setColor(c);
}

zge::Vector Player::getPosition()
{
    return zge::Vector(m_sprite.getPosition().x, m_sprite.getPosition().y);
}
