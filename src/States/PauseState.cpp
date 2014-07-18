#include "States/PauseState.hpp"

PauseState::PauseState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection)
{
    m_stateID = "PauseState";
}

void PauseState::handleEvent(const sf::Event& event)
{

}

void PauseState::update(float dt)
{

}

void PauseState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void PauseState::postDraw()
{

}
