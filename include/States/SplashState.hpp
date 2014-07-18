#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/State/BaseState.hpp>
#include <ZGE/State/StateCollection.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>

//SELF

class SplashState : public zge::BaseState
{
public:
    SplashState(sf::RenderWindow& window, zge::StateCollection& stateCollection);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

private:
    sf::Color fade(sf::Color c, unsigned initialAlpha, unsigned desiredAlpha, sf::Time maxTime, sf::Time curTime);

    sf::Clock m_timeSpentInState;

    sf::Text m_gameTitle;
    zge::Resource<sf::Font> m_font;
    zge::Resource<sf::Texture> m_logoTexture;
    sf::Sprite m_logoSprite;
};

#endif //SPLASHSTATE_HPP
