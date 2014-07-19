#include "States/GameState.hpp"

//STD
#include <iostream>

//3RD

//SELF
#include "States/PauseState.hpp"

GameState::GameState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection),
m_player1(window),
m_player2(window),
m_action(0)
{
    m_stateID = "GameState";
    std::cout << "[GameState] Constructor\n";

    m_player1.setColor(sf::Color(255, 180, 0));
    m_player2.setColor(sf::Color(50, 200, 50));

    m_player1.useWASD();
    m_player2.useArrow();
}

void GameState::handleEvent(const sf::Event& event)
{
    m_player1.handleEvent(event);
    m_player2.handleEvent(event);
}

void GameState::update(float dt)
{
    m_player1.update(dt);
    m_player2.update(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        m_action = 1;
    }
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_player1, states);
    target.draw(m_player2, states);
}

void GameState::postDraw()
{
    if (m_action == 1)
    {
        m_stateCollection.push<PauseState>(m_window);
        m_action = 0;
        std::cout << "PauseState Pushed\n";
    }
}
