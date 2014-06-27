//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Player.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "Multiplayer Asteroids");
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Player player1;

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

        player1.update(prevFrameTime);

        window.clear(sf::Color(40, 40, 40));
        window.draw(player1);
        window.display();

        prevFrameTime = frameTimer.restart();
    }

    return 0;
}
