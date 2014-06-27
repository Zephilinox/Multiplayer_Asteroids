#include "Player.hpp"

Player::Player():
m_Texture("textures/Player.png")
{
    m_Sprite.setTexture(m_Texture.get());
}

void Player::handleEvent(const sf::Event)
{

}

void Player::update(const sf::Time dt)
{

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
