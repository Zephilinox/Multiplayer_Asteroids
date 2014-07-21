#include "States/GameState.hpp"

//STD
#include <iostream>

//3RD
#include <ZGE/Utility.hpp>

//SELF
#include "States/PauseState.hpp"

GameState::GameState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection),
m_player1(window),
m_player2(window),
m_player1Score("", "fonts/arial.ttf", 24, sf::Vector2f(0, 0), Origin::TopLeft),
m_player2Score("", "fonts/arial.ttf", 24, sf::Vector2f(1280, 0), Origin::TopRight),
m_level(window, 0),
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

    m_player1Score.handleEvent(event);
    m_player2Score.handleEvent(event);

    m_level.handleEvent(event);
}

void GameState::update(float dt)
{
    m_player1.update(dt);
    m_player2.update(dt);

    m_level.update(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        m_action = 1;
    }

    if (m_level.getFinishState() == FinishState::Finished)
    {
        m_level.nextLevel();
    }

    for (unsigned i = 0; i < m_level.getAsteroids().size(); ++i)
    {
        Asteroid& a = m_level.getAsteroids()[i];

        for (unsigned i = 0; i < m_player1.getBulletManager().getBullets().size(); ++i)
        {
            Bullet& b = m_player1.getBulletManager().getBullets()[i];
            b.checkCollision(a.getCollisionShape());
            a.checkCollision(b.getCollisionShape());
        }

        for (unsigned i = 0; i < m_player2.getBulletManager().getBullets().size(); ++i)
        {
            Bullet& b = m_player2.getBulletManager().getBullets()[i];
            b.checkCollision(a.getCollisionShape());
            a.checkCollision(b.getCollisionShape());
        }

        //a.checkCollision(m_player1.getCollisionShape());
        m_player1.checkCollision(a.getCollisionShape());

        //a.checkCollision(m_player2.getCollisionShape());
        m_player2.checkCollision(a.getCollisionShape());
    }

    m_player1Score.setText(zge::toString(m_player1.getBulletManager().getScore()));
    m_player1Score.update(dt);

    m_player2Score.setText(zge::toString(m_player2.getBulletManager().getScore()));
    m_player2Score.update(dt);
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_player1, states);
    target.draw(m_player2, states);
    target.draw(m_level, states);
    target.draw(m_player1Score, states);
    target.draw(m_player2Score, states);
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
