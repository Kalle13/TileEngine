#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

#include "Entity.h"

class EntityManager : public sf::Drawable
{
public:

   EntityManager() : numberOfEntities(0) {}
   ~EntityManager();

   void  UpdateNumberOfEntities(unsigned newNumberOfEntities);

   void  UpdateEntities();
   void  SetEntityProperties(unsigned entityIndex, Entity *entity);

   void  SetEntityRadius(unsigned entityIndex, float newRadius);
   void  SetEntityColor(unsigned entityIndex, sf::Color newColor);
   void  SetEntityType(unsigned entityIndex, _Entity::Type newType);
   void  SetEntityPosition(unsigned entityIndex, sf::Vector2f newPosition);

   float          GetEntityRadius(unsigned entityIndex);
   sf::Color      GetEntityColor(unsigned entityIndex);
   _Entity::Type  GetEntityType(unsigned entityIndex);
   sf::Vector2f   GetEntityPosition(unsigned entityIndex);

private:

   unsigned numberOfEntities;
   Entity *entities;

private:

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      if(numberOfEntities>0){
         for(unsigned i=0;i<numberOfEntities;++i){
            target.draw(entities[i]);
         }
      }
   }
};


#endif // _ENTITY_MANAGER_H_
