//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "Player.hpp"
#include "ZGE/Utility.hpp"
#include "ZGE/State/StateHandler.hpp"
#include "ZGE/State/BaseState.hpp"
#include "States/SplashState.hpp"

int main()
{
    std::srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "Multiplayer Asteroids");
    //window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);

    zge::StateHandler stateHandler;
    stateHandler.getStateCollection().push<SplashState>(window);

    sf::Clock frameTimer;
    sf::Time prevFrameTime = sf::seconds(1.f/60.f);
    sf::Event event;

    while (window.isOpen() &&
           stateHandler.getStateCollection().getSize() > 0)
    {
        while (window.pollEvent(event))
        {
            stateHandler.handleEvent(event);

            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }

                default:
                {
                    break;
                }
            }
        }

        stateHandler.update(prevFrameTime.asSeconds());

        window.clear(sf::Color(40, 40, 40));
        stateHandler.draw(window);
        window.display();

        stateHandler.postDraw();

        prevFrameTime = frameTimer.restart();
        //std::cout << "FPS: " << 1.f / prevFrameTime.asSeconds() << "\n";
    }

    return 0;
}
