#ifndef ASTEROID_HPP
#define ASTEROID_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF

class Asteroid : public sf::Drawable
{

public:
    Asteroid();

    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void keepInWindow();

};

#endif //ASTEROID_HPP
