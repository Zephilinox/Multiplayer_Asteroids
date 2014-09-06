#ifndef LEVEL_HPP
#define LEVEL_HPP

//STD
#include <vector>

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>
#include <ZGE/TextHandler.hpp>

//SELF
#include "Asteroid.hpp"

enum FinishState {Unfinished, Finished, Lost};

/*
Perhaps have waves, so that higher levels last longer without becoming impossible due to number of asteroids on screen.
*/

class Level : public sf::Drawable
{
public:
    Level(sf::RenderWindow& window, unsigned level);
    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    FinishState getFinishState();

    void nextLevel();
    void restartLevel();

    std::vector<Asteroid>& getAsteroids() const;
    unsigned getLevel();

private:
    void spawnAsteroids();

    sf::RenderWindow& m_window;
    FinishState m_finishState;
    unsigned m_level;
    mutable std::vector<Asteroid> m_asteroids;
    zge::TextHandler m_levelTitle;
    sf::Clock m_levelCounter;
};

#endif //LEVEL_HPP
