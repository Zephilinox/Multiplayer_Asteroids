#ifndef MENU_HPP
#define MENU_HPP

//STD
#include <vector>
#include <memory>

//3RD
#include <SFML/Graphics.hpp>
//SELF
#include "Button.hpp"

class Menu : public sf::Drawable
{
public:
    Menu(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void addButton(std::string textureName, std::string buttonName);
    bool buttonClicked(std::string buttonName);

private:
    void calculateButtonPositions();

    sf::RenderWindow& m_window;
    std::vector<std::shared_ptr<Button>> m_buttons;
};

#endif //MENU_HPP
