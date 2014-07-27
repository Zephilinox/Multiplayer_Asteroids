#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/State/BaseState.hpp>
#include <ZGE/State/StateCollection.hpp>

//SELF
#include "Menu.hpp"
#include "TextHandler.hpp"

enum Winner {None, Player1, Player2};

class GameOverState : public zge::BaseState
{
public:
    GameOverState(sf::RenderWindow& window, zge::StateCollection& stateCollection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

    void setWinner(Winner);

private:
    Menu m_menu;
    TextHandler m_titleText;
    unsigned m_action;
    Winner m_winner;
};

#endif //GAMEOVERSTATE_HPP
