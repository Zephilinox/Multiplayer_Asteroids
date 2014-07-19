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
    /**
        Player 1 has to destroy the asteroids without getting hit more than x times per level.
        This is done by shooting them, which increases your score.

        Player 2 has to stop player 1 from destroying the asteroids.
        This is done by shooting Player 1's bullets.
        This is made easier by the fact that Player 2's bullets are twice as fast as well as warping around the screen one extra time.

        Player 2 can also shoot a tractor beam and a repulsion beam at an asteroid or player in order to pull it towards him. Higher mass = slower pull/push.
        Player 2's velocity will factor in to the speed at which the tractor beam functions, depending on the direction.
        By using the tractor beam, Player 2 can either force Player 1 in to a collision with an asteroid
        or force an asteroid in to a collision with Player 1

        If Player 1 dies, Player 2 swaps with Player 1. The level remains the same.

        Once both players have swapped (so one chance per role) and then die, the game will end.

        The player who scored the most while acting as Player 1 wins.
    **/

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
