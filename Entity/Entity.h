#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


namespace _Entity
{
   enum Type{Player, Item, Bot, Null};
}


class Entity : public sf::Drawable
{
public:

   Entity() : circleRadius(0), color(sf::Color::White), type(_Entity::Bot), position(sf::Vector2f(0,0)) {}

   Entity(float initRadius, sf::Color initColor, _Entity::Type entityType, sf::Vector2f initPosition) :
      circleRadius(initRadius),
      color(initColor),
      type(entityType),
      position(initPosition)
   {
      entityCircle.setOrigin(circleRadius,circleRadius);
      entityCircle.setRadius(circleRadius);
      entityCircle.setFillColor(color);
      entityCircle.setPosition(position);
      entityCircle.setPointCount(30);
   }


   // Functions to set properties without updating the entity

   void              SetProperties(float newRadius, sf::Color newColor, _Entity::Type newType, sf::Vector2f newPosition);
   void              SetRadius(float newRadius) {circleRadius = newRadius;}
   void              SetColor(sf::Color newColor) {color = newColor;}
   void              SetType(_Entity::Type newType) {type = newType;}   // Have to change Entity to different derived class type if/when Entity types are defined
   void              SetPosition(sf::Vector2f newPosition) {position = newPosition;}


   // Functions to get properties

   float             GetRadius()    {return circleRadius;}
   sf::Color         GetColor()     {return color;}
   _Entity::Type     GetType()      {return type;}
   sf::Vector2f      GetPosition()  {return position;}


   // Functions to Update Entity (set a parameter, then update the entityCircle)

   void              UpdateRadius(float newRadius);
   void              UpdateColor(sf::Color newColor);
   void              UpdatePosition(sf::Vector2f newPosition);
   void              UpdateEntity();

private:

   float             circleRadius;
   sf::Color         color;
   _Entity::Type     type;
   sf::Vector2f      position;
   sf::CircleShape   entityCircle;

private:

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
     target.draw(entityCircle);
   }
};


#endif // _ENTITY_H_
