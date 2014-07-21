#ifndef TEXTHANDLER_HPP
#define TEXTHANDLER_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>

//SELF

enum Origin {TopLeft, TopCentre, TopRight, MiddleLeft, MiddleCentre, MiddleRight, BottomLeft, BottomCentre, BottomRight};

class TextHandler: public sf::Drawable
{
public:
    TextHandler(std::string textString, std::string fontLocation, unsigned characterSize, sf::Vector2f position, Origin origin);
    void handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setText(std::string str);
    void setColor(sf::Color col);

private:
    void updatePosition();

    zge::Resource<sf::Font> m_font;
    sf::Text m_text;
    sf::Vector2f m_position;
    Origin m_origin;
};

#endif //TEXTHANDLER_HPP
