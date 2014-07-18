#ifndef BUTTON_HPP
#define BUTTON_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/ResourceManagement/Resource.hpp>

//SELF

class Button : public sf::Drawable
{
public:
    Button(sf::RenderWindow& window, std::string textureName);
    void handleEvent(const sf::Event& event);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(float dt);

    void setCharacterSize(unsigned int x);

    void setString(std::string str);
    std::string getString();

    bool mouseClicked();

    sf::Vector2u getSize();

    void setPosition(sf::Vector2f);
    sf::Vector2f getPosition();

private:
    sf::RenderWindow& m_window;
    sf::Sprite m_sprite;
    sf::Text m_text;

    bool m_mouseClicked;

    zge::Resource<sf::Texture> m_texture;
    zge::Resource<sf::Font> m_font;
};

#endif // BUTTON_HPP
