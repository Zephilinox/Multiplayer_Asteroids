#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "ZGE/State/BaseState.hpp"
#include "ZGE/State/StateCollection.hpp"
#include "Player.hpp"
#include "Level.hpp"
#include "TextHandler.hpp"

class GameState : public zge::BaseState
{
public:
    GameState(sf::RenderWindow& window, zge::StateCollection& stateCollection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

private:
    Player m_player1;
    Player m_player2;
    TextHandler m_player1Score;
    TextHandler m_player2Score;

    Level m_level;

    int m_action;
};

#endif //GAMESTATE_HPP
