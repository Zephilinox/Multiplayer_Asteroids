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
    //float height = 2 * radius * std::sin(zge::Vector::degToRad(60)); //from top to base

    zge::Vector p1 = zge::Vector::degToVector(30);
    zge::Vector p2 = zge::Vector::degToVector(90);
    zge::Vector p3 = zge::Vector::degToVector(150);
    zge::Vector p4 = zge::Vector::degToVector(210);
    zge::Vector p5 = zge::Vector::degToVector(270);
    zge::Vector p6 = zge::Vector::degToVector(330);

    cs.setPointCount(6);
    cs.setPoint(0, sf::Vector2f(p1.x, p1.y) * (2*radius+((std::rand() % (int)radius) - radius/2)));
    //cs.setPoint(1, sf::Vector2f(p2.x, p2.y) * (2*radius+((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(1, sf::Vector2f(p2.x, p2.y) * (radius + (std::rand() % 128 - 64)));
    cs.setPoint(2, sf::Vector2f(p3.x, p3.y) * (2*radius+((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(3, sf::Vector2f(p4.x, p4.y) * (2*radius+((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(4, sf::Vector2f(p5.x, p5.y) * (2*radius+((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(5, sf::Vector2f(p6.x, p6.y) * (2*radius+((std::rand() % (int)radius) - radius/2)));

    /*cs.setPoint(0, sf::Vector2f(p1.x, p1.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(1, sf::Vector2f(p2.x, p2.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    //cs.setPoint(1, sf::Vector2f(p2.x, p2.y) * (radius /3));
    cs.setPoint(2, sf::Vector2f(p3.x, p3.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(3, sf::Vector2f(p4.x, p4.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(4, sf::Vector2f(p5.x, p5.y) * (radius + ((std::rand() % (int)radius) - radius/2)));
    cs.setPoint(5, sf::Vector2f(p6.x, p6.y) * (radius + ((std::rand() % (int)radius) - radius/2)));*/
    //cs.setPoint(5, sf::Vector2f(p6.x, p6.y) * (radius / 3));

    cs.setPoint(0, sf::Vector2f(p1.x, p1.y) * radius);
    //cs.setPoint(1, sf::Vector2f(p2.x, p2.y) * radius);
    cs.setPoint(2, sf::Vector2f(p3.x, p3.y) * radius);
    cs.setPoint(3, sf::Vector2f(p4.x, p4.y) * radius);
    cs.setPoint(4, sf::Vector2f(p5.x, p5.y) * radius);
    cs.setPoint(5, sf::Vector2f(p6.x, p6.y) * radius);

    cs.setPosition(center);

    zge::Vector pos1(cs.getPoint(1).x - cs.getPoint(0).x, cs.getPoint(1).y - cs.getPoint(0).y);
    zge::Vector pos2(cs.getPoint(2).x - cs.getPoint(1).x, cs.getPoint(2).y - cs.getPoint(1).y);

    target.draw(cs, states);

    bool positiveCross = false;
    bool is_convex = false;

    for (unsigned i = 0; i < 6; ++i)
    {
        if (i == 0)
        {
            zge::Vector v1(cs.getPoint(0).x - cs.getPoint(5).x, cs.getPoint(0).y - cs.getPoint(5).y);
            zge::Vector v2(cs.getPoint(1).x - cs.getPoint(0).x, cs.getPoint(1).y - cs.getPoint(0).y);
            if (((v1.x * v2.y) - (v1.y * v2.x)) > 0)
            {
                positiveCross = true;
            }
            else
            {
                positiveCross = false;
            }
        }
        else if (i == 5)
        {
            zge::Vector v1(cs.getPoint(5).x - cs.getPoint(4).x, cs.getPoint(5).y - cs.getPoint(4).y);
            zge::Vector v2(cs.getPoint(0).x - cs.getPoint(5).x, cs.getPoint(0).y - cs.getPoint(5).y);
            if ((((v1.x * v2.y) - (v1.y * v2.x)) > 0 && positiveCross) ||
                (((v1.x * v2.y) - (v1.y * v2.x)) < 0 && !positiveCross))
            {
                is_convex = true;
            }
        }
        else
        {
            zge::Vector v1(cs.getPoint(i).x - cs.getPoint(i-1).x, cs.getPoint(i).y - cs.getPoint(i-1).y);
            zge::Vector v2(cs.getPoint(i+1).x - cs.getPoint(i).x, cs.getPoint(i+1).y - cs.getPoint(i).y);
            if ((((v1.x * v2.y) - (v1.y * v2.x)) > 0 && positiveCross) ||
                (((v1.x * v2.y) - (v1.y * v2.x)) < 0 && !positiveCross))
            {
                is_convex = true;
            }
        }
    }

    std::cout << "Is convex? " << is_convex << "\n";

    //if (is_convex) sf::sleep(sf::seconds(1.2f));

    //std::cout << zge::Vector::radToDeg(std::atan2((pos1.x * pos2.y) - (pos2.x * pos1.y), pos1.dot(pos2))) << "\n";
    std::cout << (zge::Vector(0, -1)).dot(zge::Vector(1, 0)) << "\n";
    //std::cout << zge::Vector::radToDeg(std::atan2((0 * 1) - (1 * 0), )) << "\n";

    cs.getPoint(0);
    cs.getPoint(1);
    cs.getPoint(2);

    double areaSum = 0;
    areaSum += cs.getPoint(0).x * (-cs.getPoint(2).y - -cs.getPoint(1).y);
    areaSum += cs.getPoint(1).x * (-cs.getPoint(0).y - -cs.getPoint(2).y);
    areaSum += cs.getPoint(2).x * (-cs.getPoint(1).y - -cs.getPoint(0).y);

    int winding = 0;
    zge::Vector v1(cs.getPoint(0).x - cs.getPoint(5).x, cs.getPoint(0).y - cs.getPoint(5).y);
    zge::Vector v2(cs.getPoint(1).x - cs.getPoint(0).x, cs.getPoint(1).y - cs.getPoint(0).y);
    if (((v1.x * v2.y) - (v1.y * v2.x)) > 0)
    {
        std::cout << "winding > 0\n";
        winding = 1;
    }
    else
    {
        std::cout << "winding < 0\n";
        winding = -1;
    }


    std::cout << areaSum << "\n";

    if (winding == 1)
    {
        if (areaSum < 0)
        {
            //sf::sleep(sf::seconds(1.f));
        }
        else
        {
            sf::sleep(sf::seconds(0.5f));
        }
    }
    else if (winding == -1)
    {
        if (areaSum > 0)
        {
            //sf::sleep(sf::seconds(1.f));
        }
        else
        {
            sf::sleep(sf::seconds(0.5f));
        }
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
