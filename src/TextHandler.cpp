#include "TextHandler.hpp"

TextHandler::TextHandler(std::string textString, std::string fontLocation, unsigned characterSize, sf::Vector2f position, Origin origin):
m_font(fontLocation),
m_position(position),
m_origin(origin)
{
    m_text.setFont(m_font);
    m_text.setString(textString);
    m_text.setCharacterSize(characterSize);

    updatePosition();
}

void TextHandler::handleEvent(const sf::Event& event)
{

}

void TextHandler::update(float dt)
{
    updatePosition();
}

void TextHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}

void TextHandler::setText(std::string str)
{
    m_text.setString(str);
}

void TextHandler::setColor(sf::Color col)
{
    m_text.setColor(col);
}

sf::Color TextHandler::getColor()
{
    return m_text.getColor();
}

void TextHandler::updatePosition()
{
    switch(m_origin)
    {
        case Origin::TopLeft:
        {
            m_text.setPosition(m_position.x,
                               m_position.y);
            break;
        }

        case Origin::TopRight:
        {
            m_text.setPosition(m_position.x - (m_text.getLocalBounds().width + m_text.getLocalBounds().left),
                               m_position.y);
            break;
        }

        case Origin::TopCentre:
        {
            m_text.setPosition(m_position.x - ((m_text.getLocalBounds().width + m_text.getLocalBounds().left)/2),
                               m_position.y);
            break;
        }

        case Origin::MiddleCentre:
        default:
        {
            m_text.setPosition(m_position.x - ((m_text.getLocalBounds().width + m_text.getLocalBounds().left)/2),
                               m_position.y - ((m_text.getLocalBounds().height + m_text.getLocalBounds().top))/2);
            break;
        }
    }
}
