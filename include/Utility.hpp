#ifndef UTILITY_HPP
#define UTILITY_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF

namespace utility
{

void drawLine(sf::RenderTarget& target, float x1, float y1, float x2, float y2, sf::Color c)
{
    sf::VertexArray line(sf::Lines, 2);
    line[0] = sf::Vertex(sf::Vector2f(x1, y1), c);
    line[1] = sf::Vertex(sf::Vector2f(x2, y2), c);
    target.draw(line);
}

}


#endif // UTILITY_HPP
