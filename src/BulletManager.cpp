#include "BulletManager.hpp"

BulletManager::BulletManager()
{

}

void BulletManager::handleEvent(const sf::Event event)
{
    for (Bullet& b : m_bullets)
    {
        b.handleEvent(event);
    }
}

void BulletManager::update(float dt)
{
    for (Bullet& b : m_bullets)
    {
        b.update(dt);
    }

    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),
                                   [](Bullet b)
                                    {
                                        return b.getWarpCount() > 1;
                                    }
                                   ), m_bullets.end());
}

void BulletManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (Bullet b : m_bullets)
    {
        target.draw(b, states);
    }
}

void BulletManager::createBullet(sf::Vector2f pos, float rotation, float speed, sf::Color col)
{
    m_bullets.push_back(Bullet(pos, rotation, speed, col));
}
