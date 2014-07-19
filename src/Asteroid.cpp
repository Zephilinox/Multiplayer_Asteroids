#include "Asteroid.hpp"

Asteroid::Asteroid()
{
}

void Asteroid::handleEvent(const sf::Event& event)
{

}

void Asteroid::update(float dt)
{

}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void Asteroid::keepInWindow()
{
    /*if (m_sprite.getPosition().x + (m_texture->getSize().x / 2) <= 0)
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
    }*/
}
