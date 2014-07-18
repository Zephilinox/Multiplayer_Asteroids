#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/State/BaseState.hpp>

//SELF

class PauseState : public zge::BaseState
{
public:
    PauseState(sf::RenderWindow& window, zge::StateCollection& stateCollection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

private:
};

#endif //PAUSESTATE_HPP
