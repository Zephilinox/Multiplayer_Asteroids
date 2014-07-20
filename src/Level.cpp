#include "Level.hpp"

//STD

//3RD
#include <ZGE/Utility.hpp>

//SELF

Level::Level(sf::RenderWindow& window, unsigned level):
m_window(window),
m_finishState(FinishState::Unfinished),
m_level(level),
m_font("fonts/arial.ttf")
{
    m_levelTitle.setFont(m_font);
    m_levelTitle.setCharacterSize(32);

    restartLevel();

}

void Level::handleEvent(const sf::Event& event)
{
    for (Asteroid& a : m_asteroids)
    {
        a.handleEvent(event);
    }
}

void Level::update(float dt)
{
    for (Asteroid& a : m_asteroids)
    {
        a.update(dt);
    }

    if (m_levelCounter.getElapsedTime().asSeconds() >= 5.f)
    {
        m_finishState = FinishState::Finished;
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (Asteroid& a : m_asteroids)
    {
        target.draw(a, states);
    }

    if (m_levelCounter.getElapsedTime().asSeconds() <= 2.f)
    {
        target.draw(m_levelTitle, states);
    }
}

FinishState Level::getFinishState()
{
    return m_finishState;
}

void Level::nextLevel()
{
    m_level++;
    restartLevel();
}

void Level::restartLevel()
{
    m_asteroids.clear();
    spawnAsteroids();

    m_levelCounter.restart();
    m_finishState = FinishState::Unfinished;

    m_levelTitle.setString("Level " + zge::toString(m_level));
    m_levelTitle.setPosition(m_window.getView().getCenter().x - (m_levelTitle.getLocalBounds().width - m_levelTitle.getLocalBounds().left)/2,
                             m_levelTitle.getLocalBounds().height + m_levelTitle.getLocalBounds().top);
}

std::vector<Asteroid>& Level::getAsteroids() const
{
    return m_asteroids;
}

void Level::spawnAsteroids()
{
    for (unsigned i = 0; i < (m_level+1) * 3; ++i)
    {
        //These will need to be modified for the future so that the difficulty is more gradual..
        Asteroid a(sf::Vector2f(std::rand() % 1280, std::rand() % 720), (std::rand() % 8) + 5, (std::rand() % 1300) + 200);
        m_asteroids.push_back(a);
    }
}
