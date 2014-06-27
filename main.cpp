//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "Multiplayer Asteroids");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        window.clear(sf::Color(40, 40, 40));
        window.display();
    }

    return 0;
}
