#include "Level.hpp"

Level::Level(sf::RenderWindow& window, unsigned level):
m_window(window),
m_finishState(FinishState::Unfinished),
m_level(level),
m_font("fonts/arial.ttf")
{
    spawnAsteroids();

    m_levelTitle.setFont(m_font);
    m_levelTitle.setString("Level " + m_level);
    m_levelTitle.setPosition(m_window.getView().getCenter().x - m_levelTitle.getLocalBounds().width - m_levelTitle.getLocalBounds().left,
                             m_levelTitle.getLocalBounds().height + m_levelTitle.getLocalBounds().top);
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
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (Asteroid a : m_asteroids)
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
    m_asteroids.clear();
    spawnAsteroids();
}

void Level::restartLevel()
{
    m_asteroids.clear();
    spawnAsteroids();
}

void Level::spawnAsteroids()
{
    for (unsigned i = 0; i < (m_level+1) * 5; ++i)
    {
        //These will need to be modified for the future so that the difficulty is more gradual..
        Asteroid a(sf::Vector2f(std::rand() % 1280, std::rand() % 720), (std::rand() % 8) + 5, (std::rand() % 1300) + 200);
        m_asteroids.push_back(a);
    }
}
