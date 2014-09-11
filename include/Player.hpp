#ifndef PLAYER_HPP
#define PLAYER_HPP

//STD
#include <vector>

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>
#include <ZGE/Vector.hpp>
#include <ZGE/KeybindingCache.hpp>
#include <ZGE/Collider.hpp>

//SELF
#include "BulletManager.hpp"
#include "Level.hpp"

class Player : public sf::Drawable, public zge::Collider
{
public:
    Player(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void useWASD();
    void useArrow();

    void setColor(sf::Color c);
    void setGravityPosition(zge::Vector pos);

    zge::Vector getPosition();
    BulletManager& getBulletManager();
    unsigned getLives();

    bool isInvincible();

    void handleCollision(sf::CircleShape otherColShape) override;

private:
    void movement(float dt);
    void capVelocity();
    void keepInWindow();

    sf::RenderWindow& m_window;
    mutable sf::Sprite m_sprite;
    mutable zge::Resource<sf::Texture> m_texture;

    float m_acceleration;
    zge::Vector m_velocity;
    float m_maxVelocityLength;

    KeybindingCache m_keys;

    BulletManager m_bulletManager;
    sf::Clock m_shootCooldown;
    sf::Time m_shootDelay;

    mutable bool m_isColliding;

    unsigned m_lives;

    sf::Clock m_flashingTime;
    sf::Time m_flashingDuration;
    bool m_wasDamaged;
};

#endif //PLAYER_HPP
