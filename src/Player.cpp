#include "Player.hpp"

//STD
#include <cmath>

//3RD

//SELF
#include "ZGE/Utility.hpp"

Player::Player(sf::RenderWindow& window):
Collider(32),
m_window(window),
m_texture("textures/ship.png"),
m_acceleration(200),
m_maxVelocityLength(m_acceleration * 2),
m_shootDelay(sf::seconds(0.15f))
{
    m_texture->setSmooth(true);

    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture->getSize().x / 2,
                       m_texture->getSize().y / 2);

    m_sprite.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);
    useWASD();

    m_collisionShape.setFillColor(sf::Color(0, 255, 255, 100));
}

void Player::handleEvent(const sf::Event& event)
{
    m_bulletManager.handleEvent(event);
}

void Player::update(float dt)
{
    m_bulletManager.update(dt);

    movement(dt);

    if (sf::Keyboard::isKeyPressed(m_keys.get("Decelerate")))
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

    capVelocity();

    m_sprite.move(m_velocity.x * dt, m_velocity.y * dt);

    //Attempt to spawn bullet in more accurate location, by basing it off of the likely position of the ship next frame
    //as well as spawning it using the latest sprite location (as this is located after we move the sprite
    if (sf::Keyboard::isKeyPressed(m_keys.get("Shoot")) &&
        m_shootCooldown.getElapsedTime().asSeconds() >= m_shootDelay.asSeconds())
    {
        m_shootCooldown.restart();
        sf::Vector2f gunPos = m_sprite.getPosition();
        gunPos.x += m_velocity.x * dt;
        gunPos.y += m_velocity.y * dt;
        m_bulletManager.createBullet(gunPos, m_sprite.getRotation() + (std::rand() % 6 - 3), 800, m_sprite.getColor());
    }

    keepInWindow();

    updateCollisionShape(m_sprite.getPosition(),
                         ((m_texture->getSize().x / 2) + (m_texture->getSize().y / 2)) / 2, //radius
                         m_sprite.getRotation());
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_bulletManager, states);

    target.draw(m_sprite, states);
}

void Player::useWASD()
{
    m_keys.add("Forwards", sf::Keyboard::Key::W);
    m_keys.add("Backwards", sf::Keyboard::Key::S);
    m_keys.add("Left", sf::Keyboard::Key::A);
    m_keys.add("Right", sf::Keyboard::Key::D);
    m_keys.add("Decelerate", sf::Keyboard::Key::LShift);
    m_keys.add("Shoot", sf::Keyboard::Key::Space);
}

void Player::useArrow()
{
    m_keys.add("Forwards", sf::Keyboard::Key::Up);
    m_keys.add("Backwards", sf::Keyboard::Key::Down);
    m_keys.add("Left", sf::Keyboard::Key::Left);
    m_keys.add("Right", sf::Keyboard::Key::Right);
    m_keys.add("Decelerate", sf::Keyboard::Key::RShift);
    m_keys.add("Shoot", sf::Keyboard::Key::RControl);
}

void Player::setColor(sf::Color c)
{
    m_sprite.setColor(c);
}

zge::Vector Player::getPosition()
{
    return zge::Vector(m_sprite.getPosition().x, m_sprite.getPosition().y);
}

BulletManager& Player::getBulletManager()
{
    return m_bulletManager;
}

void Player::movement(float dt)
{
    double shipRadian = zge::Vector::degToRad(m_sprite.getRotation());
    double sinRadian = std::sin(shipRadian);
    double cosRadian = std::cos(shipRadian);

    if (sf::Keyboard::isKeyPressed(m_keys.get("Forwards")))
    {
        m_velocity.x += m_acceleration * sinRadian * dt;
        m_velocity.y += -1 * m_acceleration * cosRadian * dt;
    }

    if (sf::Keyboard::isKeyPressed(m_keys.get("Backwards")))
    {
        m_velocity.x += -1 * m_acceleration * sinRadian * dt;
        m_velocity.y += m_acceleration * cosRadian * dt;
    }

    if (sf::Keyboard::isKeyPressed(m_keys.get("Left")))
    {
        m_sprite.rotate(-200 * dt);
    }

    if (sf::Keyboard::isKeyPressed(m_keys.get("Right")))
    {
        m_sprite.rotate(200 * dt);
    }
}

void Player::capVelocity()
{
    if (m_velocity.length() > m_maxVelocityLength)
    {
        m_velocity *= m_maxVelocityLength / m_velocity.length();
    }
}

void Player::keepInWindow()
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
}

void Player::handleCollision(sf::CircleShape otherColShape)
{

}
