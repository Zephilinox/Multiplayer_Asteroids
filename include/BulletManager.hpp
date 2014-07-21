#ifndef BULLETMANAGER_HPP
#define BULLETMANAGER_HPP

//STD
#include <vector>

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Bullet.hpp"

class BulletManager : public sf::Drawable
{
public:
    BulletManager();
    void handleEvent(const sf::Event event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void createBullet(sf::Vector2f pos, float rotation, float speed, sf::Color col);

    std::vector<Bullet>& getBullets();
    float getScore();

private:
    std::vector<Bullet> m_bullets;

    float m_score;
};

#endif //BULLETMANAGER_HPP
