#include "GameState.hpp"

//STD
#include <iostream>

GameState::GameState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection)
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
    //std::cout << "[GameState] handleEvent\n";
    m_player1.handleEvent(event);
    m_player2.handleEvent(event);
}

void GameState::update(float dt)
{
    //std::cout << "[GameState] update\n";
    m_player1.update(dt);
    m_player2.update(dt);
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //std::cout << "[GameState] draw\n";
    target.draw(m_player1, states);
    target.draw(m_player2, states);
}

void GameState::postDraw()
{
    //removes state from the game
    //since it's stored as a shared ptr, it will remain alive until there are no more references
    //which will be until this function ends

    //m_stateCollection.pop();
    //m_stateCollection.push<GameState>(m_window);
}
