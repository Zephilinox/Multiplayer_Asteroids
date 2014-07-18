#include "States/MenuState.hpp"

//STD

//3RD

//SELF
#include "States/GameState.hpp"

MenuState::MenuState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection),
m_menu(window)
{
    m_stateID = "MenuState";

    m_menu.addButton("textures/button.png", "New Game");
    m_menu.addButton("textures/button.png", "Quit");
}

void MenuState::handleEvent(const sf::Event& event)
{
    m_menu.handleEvent(event);
}

void MenuState::update(float dt)
{
    m_menu.update(dt);

    if (m_menu.buttonClicked("New Game"))
    {
        m_action = 1;
    }
    else if (m_menu.buttonClicked("Quit"))
    {
        m_action = 2;
    }
}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_menu, states);
}

void MenuState::postDraw()
{
    if (m_action == 1)
    {
        m_stateCollection.pop();
        m_stateCollection.push<GameState>(m_window);
    }
    else if (m_action == 2)
    {
        m_window.close();
    }
}
