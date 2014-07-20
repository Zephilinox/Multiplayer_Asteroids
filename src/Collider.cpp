#include "Collider.hpp"

Collider::Collider(unsigned sides)
{
    m_collisionShape.setPointCount(sides);
}

bool Collider::checkCollision(sf::CircleShape otherColShape)
{
    sf::CircleShape colShape = getCollisionShape();

    zge::Vector distance(colShape.getPosition().x - otherColShape.getPosition().x,
                         colShape.getPosition().y - otherColShape.getPosition().y);

    if (distance.length() < colShape.getRadius() + otherColShape.getRadius())
    {
        handleCollision(otherColShape);
        return true;
    }

    return false;
}

void Collider::updateCollisionShape(sf::Vector2f pos, float radius, float rotation)
{
    m_collisionShape.setPosition(pos);
    m_collisionShape.setRadius(radius);
    m_collisionShape.setRotation(rotation);
    m_collisionShape.setOrigin(radius, radius);
}

sf::CircleShape Collider::getCollisionShape() const
{
    return m_collisionShape;
}
