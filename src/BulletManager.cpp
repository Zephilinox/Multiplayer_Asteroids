#include "BulletManager.hpp"

BulletManager::BulletManager():
m_score(0)
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
                                   [this](Bullet& b)
                                    {
                                        if (!b.isAlive())
                                        {
                                            std::cout << b.getScore() << "\n";
                                            m_score += b.getScore();
                                        }

                                        return (b.getWarpCount() > 1) || !b.isAlive();
                                    }
                                   ), m_bullets.end());
}

void BulletManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Don't use for-each as it creates a local copy each time
    for (unsigned i = 0; i < m_bullets.size(); ++i)
    {
        target.draw(m_bullets[i], states);
    }
}

std::vector<Bullet>& BulletManager::getBullets()
{
    return m_bullets;
}

void BulletManager::createBullet(sf::Vector2f pos, float rotation, float speed, sf::Color col)
{
    m_bullets.push_back(Bullet(pos, rotation, speed, col));
}

float BulletManager::getScore()
{
    return m_score;
}
