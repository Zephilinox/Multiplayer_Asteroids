#include "Level.hpp"

//STD
#include <random>
#include <ctime>

//3RD
#include <ZGE/Utility.hpp>

//SELF

Level::Level(sf::RenderWindow& window, unsigned level):
m_window(window),
m_finishState(FinishState::Unfinished),
m_level(level),
m_levelTitle("", "fonts/arial.ttf", 32, sf::Vector2f(m_window.getView().getCenter().x, 0), zge::Origin::BottomCentre),
m_asteroidCount("", "fonts/arial.ttf", 24, sf::Vector2f(m_window.getView().getCenter().x, m_window.getView().getSize().y), zge::Origin::BottomCentre)
{
    m_asteroidCount.enableBorder(true);
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
            int numSplits = std::rand() % 3 + 2;
            while (numSplits > 0)
            {
                m_asteroids.push_back(m_asteroids[i].split(m_window.getView().getSize()));
                numSplits--;
            }
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

    m_asteroidCount.setText("Asteroids: " + zge::toString(m_asteroids.size()));
    m_asteroidCount.update(dt);
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

    target.draw(m_asteroidCount, states);
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

    m_levelTitle.setText("Level " + zge::toString(m_level));
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
    //Using C++11 Random Number Generator, as std::rand() has a limit which could be exceeded in this case, causing truncation.
    std::default_random_engine generator(std::time(0));

    int length = m_window.getView().getSize().x * (2 + (m_level / 4)); //min 2, +1 every 4 levels
    int height = m_window.getView().getSize().y * (2 + (m_level / 4));

    std::uniform_int_distribution<int> lengthDistr((length/-2), length/2);
    std::uniform_int_distribution<int> heightDistr((height/-2), height/2);

    sf::Vector2f pos (-1, -1);

    for (unsigned i = 0; i < int((m_level+3) * 1.75); ++i)
    {
        do
        {
            //We add half the actual sizes in order to evenly distribute the asteroids around the screen
            pos = sf::Vector2f(lengthDistr(generator) + (m_window.getView().getSize().x/2),
                               lengthDistr(generator) + (m_window.getView().getSize().y/2));

        } while (pos.x > 0 && pos.x < m_window.getView().getSize().x &&
                 pos.y > 0 && pos.y < m_window.getView().getSize().y);

        Asteroid a(pos,
                   (std::rand() % 8) + 5,
                   (std::rand() % 200) + 50,
                   m_window.getView().getSize());
        m_asteroids.push_back(a);
    }
}
