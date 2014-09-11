#include "Player.hpp"

//STD
#include <cmath>

//3RD
#include <ZGE/Lua.hpp>
#include <ZGE/Utility.hpp>

//SELF

Player::Player(sf::RenderWindow& window)
    : Collider(32)
    , m_window(window)
    , m_texture("textures/ship.png")
    , m_acceleration(200)
    , m_maxVelocityLength(m_acceleration * 2)
    , m_shootDelay(sf::seconds(0.15f))
    , m_lives(8)
    , m_flashingDuration(sf::seconds(3.f))
    , m_wasDamaged(false)
{
    m_texture->setSmooth(true);

    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture->getSize().x / 2,
                       m_texture->getSize().y / 2);

    m_sprite.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);

    m_collisionShape.setFillColor(sf::Color(0, 255, 255, 100));
}

void Player::handleEvent(const sf::Event& event)
{
    m_bulletManager.handleEvent(event);
}

void Player::update(float dt)
{
    m_bulletManager.update(dt, m_window);

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

    if (m_wasDamaged && m_flashingTime.getElapsedTime() > m_flashingDuration)
    {
        m_wasDamaged = false;
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_bulletManager, states);

    if (m_wasDamaged && m_flashingTime.getElapsedTime() <= m_flashingDuration)
    {
        int mili = m_flashingTime.getElapsedTime().asMilliseconds();
        int percentage = 20;
        int remMili = mili % 1000 % (percentage*10); //Ignore seconds, then get a percentage of the remainder as total blink/unblink duration
        if (remMili < (percentage*10/2)) // if div 2, then blink half the time
        {
            target.draw(m_sprite, states);
        }
    }
    else
    {
        target.draw(m_sprite, states);
    }
}

void Player::useControls(std::string luaGlobal)
{
    zge::Lua luaState;
    luaState.loadFile("variables.lua");
    luaState.executeFile("variables.lua");

    sf::Keyboard::Key forwards = sf::Keyboard::Key(luaState.getGlobal<int>(luaGlobal + ".controls.forwards"));
    sf::Keyboard::Key backwards = sf::Keyboard::Key(luaState.getGlobal<int>(luaGlobal + ".controls.backwards"));
    sf::Keyboard::Key left = sf::Keyboard::Key(luaState.getGlobal<int>(luaGlobal + ".controls.left"));
    sf::Keyboard::Key right = sf::Keyboard::Key(luaState.getGlobal<int>(luaGlobal + ".controls.right"));
    sf::Keyboard::Key decelerate = sf::Keyboard::Key(luaState.getGlobal<int>(luaGlobal + ".controls.decelerate"));
    sf::Keyboard::Key shoot = sf::Keyboard::Key(luaState.getGlobal<int>(luaGlobal + ".controls.shoot"));

    m_keys.add("Forwards", forwards);
    m_keys.add("Backwards", backwards);
    m_keys.add("Left", left);
    m_keys.add("Right", right);
    m_keys.add("Decelerate", decelerate);
    m_keys.add("Shoot", shoot);
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

unsigned Player::getLives()
{
    return m_lives;
}

bool Player::isInvincible()
{
    return m_wasDamaged;
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
        m_sprite.setPosition(m_window.getView().getSize().x, m_sprite.getPosition().y);
    }
    else if (m_sprite.getPosition().x - (m_texture->getSize().x / 2) >= m_window.getView().getSize().x)
    {
        m_sprite.setPosition(0, m_sprite.getPosition().y);
    }
    else if (m_sprite.getPosition().y + (m_texture->getSize().y / 2 ) <= 0)
    {
        m_sprite.setPosition(m_sprite.getPosition().x, m_window.getView().getSize().y);
    }
    else if (m_sprite.getPosition().y - (m_texture->getSize().y / 2) >= m_window.getView().getSize().y)
    {
        m_sprite.setPosition(m_sprite.getPosition().x, 0);
    }
}

void Player::handleCollision(sf::CircleShape otherColShape)
{
    if (m_lives > 0)
    {
        m_lives--;
        std::cout << m_lives << "\n";
    }

    m_wasDamaged = true;
    m_flashingTime.restart();
}
