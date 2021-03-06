#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/TextHandler.hpp>
#include <ZGE/State/BaseState.hpp>
#include <ZGE/State/StateCollection.hpp>

//SELF
#include "Player.hpp"
#include "Level.hpp"

class GameState : public zge::BaseState
{
public:
    GameState(sf::RenderWindow& window, zge::StateCollection& stateCollection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

    void useOnePlayer();

private:
    Player m_player1;
    Player m_player2;
    zge::TextHandler m_player1Score;
    zge::TextHandler m_player1Lives;
    zge::TextHandler m_player2Score;
    zge::TextHandler m_player2Lives;

    Level m_level;

    int m_action;

    bool m_onePlayer;
};

#endif //GAMESTATE_HPP
