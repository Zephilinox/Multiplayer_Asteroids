#include "States/SplashState.hpp"

SplashState::SplashState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection)
{
    m_stateID = "SplashState";
}

void SplashState::handleEvent(const sf::Event& event)
{

}

void SplashState::update(float dt)
{

}

void SplashState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void SplashState::postDraw()
{

}
