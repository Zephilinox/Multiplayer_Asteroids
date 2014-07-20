#ifndef COLLIDER_HPP
#define COLLIDER_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include <ZGE/Vector.hpp>

class Collider
{
public:
    Collider(unsigned sides);
    virtual ~Collider() = default;

    virtual void handleCollision(sf::CircleShape otherColShape) = 0;
    bool checkCollision(sf::CircleShape otherColShape);

    void updateCollisionShape(sf::Vector2f pos, float radius, float rotation);

    sf::CircleShape getCollisionShape() const;

protected:
    sf::CircleShape m_collisionShape;
};

#endif //COLLIDER_HPP
