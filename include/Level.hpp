#ifndef LEVEL_HPP
#define LEVEL_HPP

//STD
#include <vector>

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>

//SELF
#include "Asteroid.hpp"

enum FinishState {Unfinished, Finished, Lost};

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

private:
    void spawnAsteroids();

    sf::RenderWindow& m_window;
    FinishState m_finishState;
    unsigned m_level;
    std::vector<Asteroid> m_asteroids;
    zge::Resource<sf::Font> m_font;
    sf::Text m_levelTitle;
    sf::Clock m_levelCounter;
};

#endif //LEVEL_HPP
