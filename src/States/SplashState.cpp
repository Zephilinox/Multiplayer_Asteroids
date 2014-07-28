#include "States/SplashState.hpp"

//STD

//3RD

//SELF
#include "States/MenuState.hpp"

SplashState::SplashState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection),
m_gameTitle("Multiplayer Asteroids!", "fonts/arial.ttf", 48, sf::Vector2f(m_window.getView().getCenter().x, m_window.getView().getCenter().y / 2.5), zge::Origin::MiddleCentre),
m_font("fonts/arial.ttf"),
m_logoTexture("textures/ZX-128.png")
{
    m_stateID = "SplashState";

    /*m_gameTitle.setFont(m_font);
    //m_gameTitle.setColor(sf::Color(255, 255, 255, 0));
    m_gameTitle.setCharacterSize(36);
    m_gameTitle.setString("Multiplayer Asteroids!");
    m_gameTitle.setPosition((window.getSize().x / 2) - ((m_gameTitle.getLocalBounds().width + m_gameTitle.getLocalBounds().left) / 2),
                            m_gameTitle.getLocalBounds().height + m_gameTitle.getLocalBounds().top + (window.getSize().y / 5));*/

    m_logoSprite.setTexture(m_logoTexture);
    m_logoSprite.setColor(sf::Color(255, 255, 255, 0));
    m_logoSprite.setPosition((window.getSize().x / 2) - (m_logoTexture->getSize().x / 2),
                             (m_window.getSize().y / 2) - (m_logoTexture->getSize().y / 2));
}

void SplashState::handleEvent(const sf::Event& event)
{
    m_gameTitle.handleEvent(event);
}

void SplashState::update(float dt)
{
    m_gameTitle.update(dt);

    if (m_timeSpentInState.getElapsedTime().asSeconds() <= 0.5f)
    {

    }
    else if (m_timeSpentInState.getElapsedTime().asSeconds() <= 1.5f)
    {
        //m_gameTitle.setColor(fade(m_gameTitle.getColor(), 0, 255, sf::seconds(1.f), m_timeSpentInState.getElapsedTime() - sf::seconds(0.5f)));
        m_logoSprite.setColor(fade(m_logoSprite.getColor(), 0, 255, sf::seconds(1.f), m_timeSpentInState.getElapsedTime() - sf::seconds(0.5f)));
    }
    else if (m_timeSpentInState.getElapsedTime().asSeconds() >= 1.5f &&
             m_timeSpentInState.getElapsedTime().asSeconds() <= 2.5f)
    {
        m_gameTitle.setColor(fade(m_gameTitle.getColor(), 255, 0, sf::seconds(1.f), m_timeSpentInState.getElapsedTime() - sf::seconds(1.5f)));
        m_logoSprite.setColor(fade(m_logoSprite.getColor(), 255, 0, sf::seconds(1.f), m_timeSpentInState.getElapsedTime() - sf::seconds(1.5f)));
    }

}

void SplashState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_logoSprite, states);
    target.draw(m_gameTitle, states);
}

void SplashState::postDraw()
{
    if (m_timeSpentInState.getElapsedTime().asSeconds() >= 3.0f)
    {
        m_stateCollection.push<MenuState>(m_window);
    }
}

sf::Color SplashState::fade(sf::Color c, unsigned initialAlpha, unsigned desiredAlpha, sf::Time maxTime, sf::Time curTime)
{
    sf::Color retColor = c;
    if (curTime > maxTime) curTime = maxTime;

    if (c.a < desiredAlpha)
    {
        retColor.a = desiredAlpha * (curTime.asSeconds() / maxTime.asSeconds());
    }
    else
    {
        retColor.a = initialAlpha * (1.f - (curTime.asSeconds() / maxTime.asSeconds()));
    }

    return retColor;
}
