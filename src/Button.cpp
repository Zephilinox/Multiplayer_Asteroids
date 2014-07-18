#include "Button.hpp"

//STD
#include <iostream>

Button::Button(sf::RenderWindow& window, std::string textureName):
m_window(window),
m_mouseClicked(false),
m_texture("textures/Button.png"),
m_font("fonts/arial.ttf")
{
    m_sprite.setTexture(m_texture.get());
    m_text.setFont(m_font.get());
}

void Button::handleEvent(const sf::Event& event)
{
    m_mouseClicked = false; //reset it to false each frame

    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                m_mouseClicked = true; //Set it to true if the mouse was clicked, then we set it to false later if it's not this button that was clicked.
            }
            break;
        }

        default:
        {
            break;
        }
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
    target.draw(m_text, states);
}

void Button::update(float dt)
{
    if (sf::Mouse::getPosition(m_window).x > m_sprite.getPosition().x &&
        sf::Mouse::getPosition(m_window).x < m_sprite.getPosition().x + this->getSize().x)
    {
        if (sf::Mouse::getPosition(m_window).y > m_sprite.getPosition().y &&
        sf::Mouse::getPosition(m_window).y < m_sprite.getPosition().y + this->getSize().y)
        {
            m_text.setColor(sf::Color(255, 180, 0));
        }
        else
        {
            m_text.setColor(sf::Color::White);
            m_mouseClicked = false; //Not our button, so set to false
        }
    }
    else
    {
        m_mouseClicked = false; //Not our button, so set to false
        m_text.setColor(sf::Color::White);
    }
}

void Button::setCharacterSize(unsigned int x)
{
    m_text.setCharacterSize(x);
    setString(m_text.getString()); //Recenter text
}

void Button::setString(std::string str)
{
    m_text.setString(str);
    m_text.setPosition(m_sprite.getPosition().x + (m_sprite.getTexture()->getSize().x/2) - (m_text.getLocalBounds().width/2),
                       m_sprite.getPosition().y + (m_sprite.getTexture()->getSize().y/2) - (m_text.getLocalBounds().height));
}

std::string Button::getString()
{
    return m_text.getString();
}

bool Button::mouseClicked()
{
    //we need to store the value in an old variable so that we can reset it before we return from the function
    //we need to reset it because if the button does not update on the next frame (because it pushed or popped a state) then if it returns it will assume the mouse is still clicked
    bool old = m_mouseClicked;
    m_mouseClicked = false;
    return old;
}

sf::Vector2u Button::getSize()
{
    return m_sprite.getTexture()->getSize();
}

void Button::setPosition(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
    this->setString(m_text.getString()); //Recenter text
}

sf::Vector2f Button::getPosition()
{
    return m_sprite.getPosition();
}
