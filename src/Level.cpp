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
        a.update(dt, m_window);
    }

    for (unsigned i = 0; i < m_asteroids.size(); ++i)
    {
        if (!m_asteroids[i].isAlive() && m_asteroids[i].canSplit())
        {
            m_asteroids.push_back(m_asteroids[i].split());
            m_asteroids.push_back(m_asteroids[i].split());
            m_asteroids.push_back(m_asteroids[i].split());
            /*Asteroid a1(sf::Vector2f(500, 500), 6, 400);
            Asteroid a2(sf::Vector2f(500, 500), 6, 400);
            m_asteroids.push_back(a1);
            m_asteroids.push_back(a2);*/
        }
    }

    m_asteroids.erase(std::remove_if(m_asteroids.begin(), m_asteroids.end(),
                                   [](Asteroid& a)
                                    {
                                        return !a.isAlive();
                                    }
                                   ), m_asteroids.end());

    if (m_asteroids.size() == 0)
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

unsigned Level::getLevel()
{
    return m_level;
}

void Level::spawnAsteroids()
{
    for (unsigned i = 0; i < int((m_level+1) * 1.5); ++i)
    {
        //These will need to be modified for the future so that the difficulty is more gradual..
        Asteroid a(sf::Vector2f(std::rand() % int(m_window.getView().getSize().x),
                                std::rand() % int(m_window.getView().getSize().y)),
                   (std::rand() % 8) + 5,
                   (std::rand() % 200) + 50);
        m_asteroids.push_back(a);
    }
}
