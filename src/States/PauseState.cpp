#include "States/PauseState.hpp"

PauseState::PauseState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection),
m_menu(window),
m_action(0)
{
    m_stateID = "PauseState";

    m_menu.addButton("/textures/button.png", "Resume Game");
    m_menu.addButton("/textures/button.png", "Exit to Main Menu");
    m_menu.addButton("/textures/button.png", "Exit to Desktop");
}

void PauseState::handleEvent(const sf::Event& event)
{
    m_menu.handleEvent(event);
}

void PauseState::update(float dt)
{
    m_menu.update(dt);

    if (m_menu.buttonClicked("Resume Game"))
    {
        m_action = 1;
    }
    else if (m_menu.buttonClicked("Exit to Main Menu"))
    {
        m_action = 2;
    }
    else if (m_menu.buttonClicked("Exit to Desktop"))
    {
        m_action = 3;
    }
}

void PauseState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_menu, states);
}

void PauseState::postDraw()
{
    if (m_action == 1)
    {
        m_stateCollection.pop();
        m_action = 0;
    }
    else if (m_action == 2)
    {
        m_stateCollection.pop();
        m_stateCollection.pop();
        m_action = 0;
    }
    else if (m_action == 3)
    {
        m_window.close();
        m_action = 0;
    }
}
