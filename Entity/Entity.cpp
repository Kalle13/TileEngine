#include "Entity.h"


void  Entity::SetProperties(float newRadius, sf::Color newColor, _Entity::Type newType, sf::Vector2f newPosition)
{
   circleRadius   = newRadius;
   color          = newColor;
   type           = newType;
   position       = newPosition;
}


void Entity::UpdatePosition(sf::Vector2f newPosition)
{
   position = newPosition;
   entityCircle.setPosition(position);
}


void Entity::UpdateColor(sf::Color newColor)
{
   color = newColor;
   entityCircle.setFillColor(color);
}


void Entity::UpdateRadius(float newRadius)
{
   circleRadius = newRadius;
   entityCircle.setRadius(circleRadius);
   entityCircle.setOrigin(circleRadius,circleRadius);
}


void Entity::UpdateEntity()
{
   entityCircle.setOrigin(circleRadius,circleRadius);
   entityCircle.setRadius(circleRadius);
   entityCircle.setFillColor(color);
   entityCircle.setPosition(position);
   entityCircle.setPointCount(30);
}
