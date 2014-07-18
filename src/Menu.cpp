#include "Menu.hpp"

//STD
#include <iostream>

//3RD

//SELF

Menu::Menu(sf::RenderWindow& window):
m_window(window)
{
}

void Menu::handleEvent(const sf::Event& event)
{
    for (auto& b : m_buttons)
    {
        b->handleEvent(event);
    }
}

void Menu::update(float dt)
{
    for (auto& b : m_buttons)
    {
        b->update(dt);
    }
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto b : m_buttons)
    {
        b->draw(target, states);
    }
}

void Menu::addButton(std::string textureName, std::string buttonName)
{
    std::shared_ptr<Button> b(new Button(m_window, textureName));

    b->setString(buttonName);
    b->setCharacterSize(28);

    m_buttons.push_back(std::move(b));

    calculateButtonPositions();
}

bool Menu::buttonClicked(std::string buttonName)
{
    for (unsigned int i = 0; i < m_buttons.size(); ++i)
    {
        if (m_buttons[i]->getString() == buttonName && m_buttons[i]->mouseClicked())
        {
            std::cout << "Button " << m_buttons[i]->getString() << " was clicked\n";
            return true;
        }
    }

    return false;
}

void Menu::calculateButtonPositions()
{
    if (m_buttons.size() == 0) return;

    unsigned windowWidth = m_window.getSize().x;
    unsigned windowHeight = m_window.getSize().y;

    if (m_buttons.size() % 2 == 0) //if the number of buttons is even
    {
        unsigned int LowerYButton = (m_buttons.size()/2.f) - 1; //if size = 8, lower index = 4-1 = 3, upper would be 4, index is 0-based where as size is not
        m_buttons[LowerYButton]->setPosition(sf::Vector2f(windowWidth/2 - m_buttons[LowerYButton]->getSize().x/2,
                                                         windowHeight/2 - m_buttons[LowerYButton]->getSize().y)); //top-left is 0, 0; so subtract all of y to place it above center screen

        unsigned int UpperYButton = (m_buttons.size()/2.f);
        m_buttons[UpperYButton]->setPosition(sf::Vector2f(windowWidth/2 - m_buttons[UpperYButton]->getSize().x/2,
                                                         windowHeight/2)); //don't subtract size-y because the top is already in the center

        for (unsigned int i = 0; i < m_buttons.size(); ++i)
        {
            if (i < LowerYButton)
            {
                //set the y-position of all buttons with an index lower than the LowerYButton as being said buttons y-pos minus the height of the button times by the distance in index's
                m_buttons[i]->setPosition(sf::Vector2f(m_buttons[LowerYButton]->getPosition().x,
                                                      m_buttons[LowerYButton]->getPosition().y - (m_buttons[i]->getSize().y * (LowerYButton - i))));
            }
            else if (i > UpperYButton)
            {
                //set the y-position of all buttons with an index higher than the UpperYButton as being said buttons y-pos plus the height of the button times by the distance in index's
                m_buttons[i]->setPosition(sf::Vector2f(m_buttons[UpperYButton]->getPosition().x,
                                                      m_buttons[UpperYButton]->getPosition().y + (m_buttons[i]->getSize().y * (i - UpperYButton))));
            }
        }
    }
    else //odd number of buttons
    {
        unsigned int CenterYButton = std::floor(m_buttons.size()/2.f); //if size = 5, center index = 2.5 = 2, index is 0-based so index 2 = 3rd button, 2 below, 2 above, thus being center.
        m_buttons[CenterYButton]->setPosition(sf::Vector2f(windowWidth/2 - m_buttons[CenterYButton]->getSize().x/2,
                                                          windowHeight/2 - m_buttons[CenterYButton]->getSize().y/2)); //top-left is 0, 0; so subtract half of y to place it in the center

        for (unsigned int i = 0; i < m_buttons.size(); ++i)
        {
            if (i < CenterYButton)
            {
                //set the y-position of all buttons with an index lower than the CenterYButton as being said buttons y-pos minus the height of the button times by the distance in index's
                m_buttons[i]->setPosition(sf::Vector2f(m_buttons[CenterYButton]->getPosition().x,
                                                      m_buttons[CenterYButton]->getPosition().y - (m_buttons[i]->getSize().y * (CenterYButton - i))));
            }
            else if (i > CenterYButton)
            {
                //set the y-position of all buttons with an index higher than the CenterYButton as being said buttons y-pos plus the height of the button times by the distance in index's
                m_buttons[i]->setPosition(sf::Vector2f(m_buttons[CenterYButton]->getPosition().x,
                                                      m_buttons[CenterYButton]->getPosition().y + (m_buttons[i]->getSize().y * (i - CenterYButton))));
            }
        }
    }
}
