#include "States/GameState.hpp"

//STD
#include <iostream>

//3RD
#include <ZGE/Utility.hpp>
#include <ZGE/Lua.hpp>

//SELF
#include "States/PauseState.hpp"
#include "States/GameOverState.hpp"

GameState::GameState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection),
m_player1(window),
m_player2(window),
m_player1Score("", "fonts/arial.ttf", 24, sf::Vector2f(0, 0), zge::Origin::TopLeft),
m_player1Lives("", "fonts/arial.ttf", 24, sf::Vector2f(0, m_window.getSize().y), zge::Origin::BottomLeft),
m_player2Score("", "fonts/arial.ttf", 24, sf::Vector2f(m_window.getSize().x, 0), zge::Origin::TopRight),
m_player2Lives("", "fonts/arial.ttf", 24, sf::Vector2f(m_window.getSize().x, m_window.getSize().y), zge::Origin::BottomRight),
m_level(window, 1),
m_action(0),
m_onePlayer(false)
{
    m_stateID = "GameState";

    zge::Lua luaState;
    luaState.loadFile("variables.lua");
    luaState.executeFile("variables.lua");

    sf::Color player1Color = sf::Color(luaState.getGlobal<int>("settings.player1.color.r"),
                                       luaState.getGlobal<int>("settings.player1.color.g"),
                                       luaState.getGlobal<int>("settings.player1.color.b"));

    sf::Color player2Color = sf::Color(luaState.getGlobal<int>("settings.player2.color.r"),
                                       luaState.getGlobal<int>("settings.player2.color.g"),
                                       luaState.getGlobal<int>("settings.player2.color.b"));
    m_player1.setColor(player1Color);
    m_player2.setColor(player2Color);

    m_player1.useControls("settings.player1");
    m_player2.useControls("settings.player2");

    m_player1Score.enableBorder(true);
    m_player1Lives.enableBorder(true);
    m_player2Score.enableBorder(true);
    m_player2Lives.enableBorder(true);

    m_player1Score.setColor(player1Color);
    m_player1Lives.setColor(player1Color);

    m_player2Score.setColor(player2Color);
    m_player2Lives.setColor(player2Color);
}

void GameState::handleEvent(const sf::Event& event)
{
    m_player1.handleEvent(event);
    m_player1Score.handleEvent(event);
    m_player1Lives.handleEvent(event);

    if (!m_onePlayer)
    {
        m_player2.handleEvent(event);
        m_player2Score.handleEvent(event);
        m_player2Lives.handleEvent(event);
    }

    m_level.handleEvent(event);
}

void GameState::update(float dt)
{
    m_player1.update(dt);

    if (!m_onePlayer)
    {
        m_player2.update(dt);
    }

    m_level.update(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        m_action = 1; //Pause
    }

    if (m_level.getFinishState() == FinishState::Finished)
    {
        m_level.nextLevel();
    }

    if (m_level.getLevel() > 21 ||
        m_player1.getLives() == 0 ||
        m_player2.getLives() == 0)
    {
        m_action = 2; //Game Over
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

        if (!m_player1.isInvincible())
        {
            a.checkCollision(m_player1.getCollisionShape());
            m_player1.checkCollision(a.getCollisionShape());
        }

        if (!m_onePlayer)
        {
            for (unsigned i = 0; i < m_player2.getBulletManager().getBullets().size(); ++i)
            {
                Bullet& b = m_player2.getBulletManager().getBullets()[i];
                b.checkCollision(a.getCollisionShape());
                a.checkCollision(b.getCollisionShape());
            }

            if (!m_player2.isInvincible())
            {
                a.checkCollision(m_player2.getCollisionShape());
                m_player2.checkCollision(a.getCollisionShape());
            }
        }
    }

    m_player1Score.setText("Score: " + zge::toString(m_player1.getBulletManager().getScore()));
    m_player1Score.update(dt);

    m_player1Lives.setText("Lives: " + zge::toString(m_player1.getLives()));
    m_player1Lives.update(dt);

    if (!m_onePlayer)
    {
        m_player2Score.setText("Score: " + zge::toString(m_player2.getBulletManager().getScore()));
        m_player2Score.update(dt);

        m_player2Lives.setText("Lives: " + zge::toString(m_player2.getLives()));
        m_player2Lives.update(dt);
    }
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_player1, states);

    if (!m_onePlayer)
    {
        target.draw(m_player2, states);
    }

    target.draw(m_level, states);
    target.draw(m_player1Score, states);
    target.draw(m_player1Lives, states);

    if (!m_onePlayer)
    {
        target.draw(m_player2Score, states);
        target.draw(m_player2Lives, states);
    }
}

void GameState::postDraw()
{
    if (m_action == 1)
    {
        m_stateCollection.push<PauseState>(m_window);
        m_action = 0;
    }
    else if (m_action == 2)
    {
        m_stateCollection.push<GameOverState>(m_window);

        if (!m_onePlayer &&
            (m_player1.getLives() == 0 ||
            m_player2.getBulletManager().getScore() > m_player1.getBulletManager().getScore()))
        {
            dynamic_cast<GameOverState*>(&m_stateCollection.getFromTop(0))->setWinner(Winner::Player2);
        }
        else if (!m_onePlayer &&
                 (m_player2.getLives() == 0 ||
                 m_player1.getBulletManager().getScore() > m_player2.getBulletManager().getScore()))
        {
            dynamic_cast<GameOverState*>(&m_stateCollection.getFromTop(0))->setWinner(Winner::Player1);
        }
        else if (!m_onePlayer)
        {
            dynamic_cast<GameOverState*>(&m_stateCollection.getFromTop(0))->setWinner(Winner::None);
        }
        else if (m_player1.getLives() > 0)
        {
            dynamic_cast<GameOverState*>(&m_stateCollection.getFromTop(0))->setWinner(Winner::Solo);
        }
        else
        {
            dynamic_cast<GameOverState*>(&m_stateCollection.getFromTop(0))->setWinner(Winner::DidNotWin);
        }

        m_action = 0;
    }
}

void GameState::useOnePlayer()
{
    m_onePlayer = true;
    m_player2.setColor(sf::Color(0, 0, 0, 0));
    m_player2Lives.setColor(sf::Color(0, 0, 0, 0));
    m_player2Lives.setBorderColor(sf::Color(0, 0, 0, 0));
    m_player2Score.setColor(sf::Color(0, 0, 0, 0));
    m_player2Lives.setBorderColor(sf::Color(0, 0, 0, 0));
    m_player1Lives.setPosition(sf::Vector2f(m_window.getSize().x, 0));
    m_player1Lives.setOrigin(zge::Origin::TopRight);
}
