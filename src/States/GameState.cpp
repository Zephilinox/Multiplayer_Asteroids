#include "States/GameState.hpp"

//STD
#include <iostream>

//3RD

//SELF
#include "States/PauseState.hpp"

GameState::GameState(sf::RenderWindow& window, zge::StateCollection& stateCollection):
BaseState(window, stateCollection),
m_player1(window),
m_player2(window),
m_action(0)
{
    m_stateID = "GameState";
    std::cout << "[GameState] Constructor\n";

    m_player1.setColor(sf::Color(255, 180, 0));
    m_player2.setColor(sf::Color(50, 200, 50));

    m_player1.useWASD();
    m_player2.useArrow();
}

void GameState::handleEvent(const sf::Event& event)
{
    m_player1.handleEvent(event);
    m_player2.handleEvent(event);
}

void GameState::update(float dt)
{
    m_player1.update(dt);
    m_player2.update(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        m_action = 1;
    }
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_player1, states);
    target.draw(m_player2, states);

    sf::Vector2f center = m_window.getView().getCenter();

    sf::ConvexShape cs;
    float radius = 64; //from center to vertex
    float height = 2 * radius * std::sin(zge::Vector::degToRad(60)); //from top to base

    zge::Vector p1 = zge::Vector::degToVector(30);
    zge::Vector p2 = zge::Vector::degToVector(90);
    zge::Vector p3 = zge::Vector::degToVector(150);
    zge::Vector p4 = zge::Vector::degToVector(210);
    zge::Vector p5 = zge::Vector::degToVector(270);
    zge::Vector p6 = zge::Vector::degToVector(330);

    cs.setPointCount(6);

    cs.setPoint(0, sf::Vector2f(p1.x, p1.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(1, sf::Vector2f(p2.x, p2.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(1, sf::Vector2f(p2.x, p2.y) * (radius /2));
    cs.setPoint(2, sf::Vector2f(p3.x, p3.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(3, sf::Vector2f(p4.x, p4.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(4, sf::Vector2f(p5.x, p5.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    //cs.setPoint(5, sf::Vector2f(p6.x, p6.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(5, sf::Vector2f(p6.x, p6.y) * (radius / 3));


    //cs.setPoint(0, sf::Vector2f(p1.x, p1.y) * radius);
    //cs.setPoint(1, sf::Vector2f(p2.x, p2.y) * radius);
    //cs.setPoint(2, sf::Vector2f(p3.x, p3.y) * radius);
    cs.setPoint(3, sf::Vector2f(p4.x, p4.y) * radius);
    cs.setPoint(4, sf::Vector2f(p5.x, p5.y) * radius);
    //cs.setPoint(5, sf::Vector2f(p6.x, p6.y) * radius);

    cs.setPosition(center);
    //zge::Vector pos1(cs.getPoint(0).x - cs.getPoint(1).x, cs.getPoint(0).y - cs.getPoint(1).y);
    //zge::Vector pos2(cs.getPoint(2).x - cs.getPoint(1).x, cs.getPoint(2).y - cs.getPoint(1).y);

    //zge::Vector pos1(cs.getPoint(1).x - cs.getPoint(0).x, cs.getPoint(1).y - cs.getPoint(0).y);
    //zge::Vector pos2(cs.getPoint(1).x - cs.getPoint(2).x, cs.getPoint(1).y - cs.getPoint(2).y);

    zge::Vector pos1(cs.getPoint(1).x - cs.getPoint(0).x, cs.getPoint(1).y - cs.getPoint(0).y);
    zge::Vector pos2(cs.getPoint(2).x - cs.getPoint(1).x, cs.getPoint(2).y - cs.getPoint(1).y);

    //zge::Vector pos1(cs.getPoint(1).x - cs.getPoint(0).x, cs.getPoint(1).y - cs.getPoint(0).y);
    //zge::Vector pos2(cs.getPoint(2).x - cs.getPoint(0).x, cs.getPoint(2).y - cs.getPoint(0).y);

        std::cout << pos1.x << ", " << pos1.y << "\n";
        std::cout << pos2.x << ", " << pos2.y << "\n";
    target.draw(cs, states);

    sf::ConvexShape cs2 = cs;
    cs2.setFillColor(sf::Color::Red);
    cs2.setPosition(center.x,
                    center.y + height);

    target.draw(cs2, states);

    sf::ConvexShape cs3 = cs;
    cs3.setFillColor(sf::Color::Blue);
    cs3.setPosition(center.x + radius + 0.5*radius, //add half because we want center of hexagon
                    center.y + 0.5*height);

    target.draw(cs3, states);


    float angle = zge::Vector::radToDeg(std::acos(pos1.dot(pos2) / ((pos1.length() * pos2.length()))));
    std::cout << "Angle = " << angle << "\n";

    float cw_or_ccw = (pos1.x * pos2.y) - (pos1.y * pos2.x);
    std::cout << "cw_or_ccw = " << cw_or_ccw << "\n";

    if (cw_or_ccw < 0)
    {
        std::cout << "dot = " << pos1.dot(pos2) << "\n";
        std::cout << "length1 = " << pos1.length() << "\n";
        std::cout << "length2 = " << pos2.length() << "\n";
        //std::cout << "Concave!\n";
        sf::sleep(sf::seconds(0.5f));
    }

    if (pos1.dot(pos2) < 0)
    {
        std::cout << "Actual Angle: " << 360 - angle << "\n";
        sf::sleep(sf::seconds(0.5f));
    }
}

void GameState::postDraw()
{
    if (m_action == 1)
    {
        m_stateCollection.push<PauseState>(m_window);
        m_action = 0;
        std::cout << "PauseState Pushed\n";
    }
}
