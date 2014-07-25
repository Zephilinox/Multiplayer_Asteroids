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

class GameOverState : public zge::BaseState
{
public:
    GameOverState(sf::RenderWindow& window, zge::StateCollection& stateCollection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

private:
    Menu m_menu;
    TextHandler m_titleText;
    unsigned m_action;
};

#endif //GAMEOVERSTATE_HPP
