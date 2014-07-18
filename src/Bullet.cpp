#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f pos, float rotation, float speed):
m_texture("textures/bullet.png"),
m_speed(speed)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture->getSize().x / 2,
                         m_texture->getSize().y / 2);
    m_sprite.setPosition(pos);
    m_sprite.setRotation(rotation);

    m_velocity = zge::Vector::degToVector(rotation);
    m_velocity *= m_speed;
}

void Bullet::handleEvent(const sf::Event& event)
{

}

void Bullet::update(float dt)
{
    m_sprite.move(m_velocity.x * dt, m_velocity.y * dt);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
