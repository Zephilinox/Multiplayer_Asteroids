//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Player.hpp"
#include "ZGE/Utility.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "Multiplayer Asteroids");
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Player player1;
    player1.setColor(sf::Color(255, 180, 0));
    Player player2;
    player2.setColor(sf::Color(50, 200, 50));
    player2.useArrow();

    sf::Clock frameTimer;
    sf::Time prevFrameTime = sf::seconds(1.f/60.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            player1.handleEvent(event);

            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        player1.setGravityPosition(player2.getPosition());
        player1.update(prevFrameTime);

        player2.setGravityPosition(player1.getPosition());
        player2.update(prevFrameTime);

        window.clear(sf::Color(40, 40, 40));
        window.draw(player1);
        window.draw(player2);
        zge::drawLine(window, player1.getPosition().x, player1.getPosition().y, player2.getPosition().x, player2.getPosition().y, sf::Color(0, 180, 255));
        window.display();

        prevFrameTime = frameTimer.restart();
    }

    return 0;
}
