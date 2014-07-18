#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f pos, float rotation, float speed, sf::Color col):
m_texture("textures/bullet.png"),
m_speed(speed),
m_warpCount(0)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture->getSize().x / 2,
                         m_texture->getSize().y / 2);
    m_sprite.setPosition(pos);
    m_sprite.setRotation(rotation);
    m_sprite.setColor(col);

    m_velocity = zge::Vector::degToVector(rotation);
    m_velocity *= m_speed;
}

void Bullet::handleEvent(const sf::Event& event)
{

}

void Bullet::update(float dt)
{
    m_sprite.move(m_velocity.x * dt, m_velocity.y * dt);

    keepInWindow();
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

sf::Color Bullet::getColor()
{
    return m_sprite.getColor();
}

unsigned Bullet::getWarpCount()
{
    return m_warpCount;
}

void Bullet::keepInWindow()
{
    if (m_sprite.getPosition().x + (m_texture->getSize().x / 2) <= 0)
    {
        m_sprite.setPosition(1280, m_sprite.getPosition().y);
    }
    else if (m_sprite.getPosition().x - (m_texture->getSize().x / 2) >= 1280)
    {
        m_sprite.setPosition(0, m_sprite.getPosition().y);
    }
    else if (m_sprite.getPosition().y + (m_texture->getSize().y / 2 ) <= 0)
    {
        m_sprite.setPosition(m_sprite.getPosition().x, 720);
    }
    else if (m_sprite.getPosition().y - (m_texture->getSize().y / 2) >= 720)
    {
        m_sprite.setPosition(m_sprite.getPosition().x, 0);
    }
    else
    {
        return;
    }

    m_warpCount++;
}
