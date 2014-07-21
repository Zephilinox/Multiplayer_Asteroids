#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f pos, float rotation, float speed, sf::Color col):
Collider(4),
m_texture("textures/bullet.png"),
m_speed(speed),
m_velocity(1, 1),
m_warpCount(0),
m_isAlive(true),
m_score(0)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture->getSize().x / 2,
                         m_texture->getSize().y / 2);
    m_sprite.setPosition(pos);
    m_sprite.setRotation(rotation);
    m_sprite.setColor(col);

    m_velocity *= zge::Vector::degToVector(rotation);
    m_velocity *= m_speed;

    m_collisionShape.setFillColor(sf::Color(0, 255, 255, 100));
}

void Bullet::handleEvent(const sf::Event& event)
{

}

void Bullet::update(float dt)
{
    m_sprite.move(m_velocity.x * dt, m_velocity.y * dt);

    keepInWindow();

    updateCollisionShape(m_sprite.getPosition(),
                         ((m_texture->getSize().x / 2) + (m_texture->getSize().y / 2) / 2), //radius
                         m_sprite.getRotation());
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Bullet::handleCollision(sf::CircleShape otherColShape)
{
    m_score += otherColShape.getRadius();
    m_isColliding = true;
    m_isAlive = false;
}

sf::Color Bullet::getColor()
{
    return m_sprite.getColor();
}

unsigned Bullet::getWarpCount()
{
    return m_warpCount;
}

float Bullet::getScore()
{
    return m_score;
}

bool Bullet::isAlive()
{
    return m_isAlive;
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
