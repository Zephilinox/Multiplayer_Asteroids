#include "States/MenuState.hpp"

MenuState::MenuState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection)
{
    m_stateID = "MenuState";
}

void MenuState::handleEvent(const sf::Event& event)
{

}

void MenuState::update(float dt)
{

}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void MenuState::postDraw()
{

}
