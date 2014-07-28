#include "States/GameOverState.hpp"

//STD

//3RD

//SELF
#include "States/GameState.hpp"

GameOverState::GameOverState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection),
m_menu(window),
m_titleText("", "fonts/arial.ttf", 32, sf::Vector2f(m_window.getView().getCenter().x, 64), zge::Origin::TopCentre),
m_action(0),
m_winner(Winner::None)
{
    m_stateID = "GameOverState";

    m_menu.addButton("/textures/button.png", "Restart Game");
    m_menu.addButton("/textures/button.png", "Exit to Main Menu");
    m_menu.addButton("/textures/button.png", "Exit to Desktop");
}

void GameOverState::handleEvent(const sf::Event& event)
{
    m_titleText.handleEvent(event);
    m_menu.handleEvent(event);
}

void GameOverState::update(float dt)
{
    if (m_winner == Winner::None)
    {
        m_titleText.setText("Game Over! You have both won!");
    }
    else if (m_winner == Winner::Player1)
    {
        m_titleText.setText("Game Over! Player 1 is the winner!");
    }
    else if (m_winner == Winner::Player2)
    {
        m_titleText.setText("Game Over! Player 2 is the winner!");
    }

    m_titleText.update(dt);
    m_menu.update(dt);

    if (m_menu.buttonClicked("Restart Game"))
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

void GameOverState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_titleText, states);
    target.draw(m_menu, states);
}

void GameOverState::postDraw()
{
    if (m_action == 1)
    {
        m_stateCollection.pop(); //This
        m_stateCollection.pop(); //GameState
        m_stateCollection.push<GameState>(m_window); //State is now a fresh GameState
        m_action = 0;
    }
    else if (m_action == 2)
    {
        m_stateCollection.pop(); //This
        m_stateCollection.pop(); //GameState
        //State is now MenuState
        m_action = 0;
    }
    else if (m_action == 3)
    {
        m_window.close();
        m_action = 0;
    }
}

void GameOverState::setWinner(Winner winner)
{
    m_winner = winner;
}
