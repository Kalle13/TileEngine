#include "EntityManager.h"

EntityManager::~EntityManager()
{
   delete[] entities;
}

void EntityManager::UpdateNumberOfEntities(unsigned newNumberOfEntities)
{
   if(numberOfEntities>0){
      delete[] entities;
   }

   numberOfEntities = newNumberOfEntities;

   entities = new Entity[numberOfEntities];
}


void EntityManager::UpdateEntities()
{
   for(unsigned i=0;i<numberOfEntities;++i){
      entities[i].UpdateEntity();
   }
}


void EntityManager::SetEntityProperties(unsigned entityIndex, Entity *entity)
{
   if(numberOfEntities>0 && entityIndex<numberOfEntities){
      entity[entityIndex].SetProperties(entity->GetRadius(),entity->GetColor(),entity->GetType(),entity->GetPosition());
   }
}


void EntityManager::SetEntityRadius(unsigned entityIndex, float newRadius)
{
   if(numberOfEntities>0 && entityIndex<numberOfEntities){
      entities[entityIndex].SetRadius(newRadius);
   }
}


void EntityManager::SetEntityColor(unsigned entityIndex, sf::Color newColor)
{
   if(numberOfEntities>0 && entityIndex<numberOfEntities){
      entities[entityIndex].SetColor(newColor);
   }
}


void EntityManager::SetEntityType(unsigned entityIndex, _Entity::Type newType)
{
   if(numberOfEntities>0 && entityIndex<numberOfEntities){
      entities[entityIndex].SetType(newType);
   }
}


void EntityManager::SetEntityPosition(unsigned entityIndex, sf::Vector2f newPosition)
{
   if(numberOfEntities>0 && entityIndex<numberOfEntities){
      entities[entityIndex].SetPosition(newPosition);
   }
}


float EntityManager::GetEntityRadius(unsigned entityIndex)
{
   if(numberOfEntities>0 && entityIndex<numberOfEntities){
      return entities[entityIndex].GetRadius();
   }
   return -1.0;
}


sf::Color EntityManager::GetEntityColor(unsigned entityIndex)
{
   if(numberOfEntities>0 && entityIndex<numberOfEntities){
      return entities[entityIndex].GetColor();
   }
   return sf::Color::Black;
}


_Entity::Type EntityManager::GetEntityType(unsigned entityIndex)
{
   if(numberOfEntities>0 && entityIndex<numberOfEntities){
      return entities[entityIndex].GetType();
   }
   return _Entity::Null;
}


sf::Vector2f EntityManager::GetEntityPosition(unsigned entityIndex)
{
   if(numberOfEntities>0 && entityIndex<numberOfEntities){
      return entities[entityIndex].GetPosition();
   }
   return sf::Vector2f(-1.0,-1.0);
}
