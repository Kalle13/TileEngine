#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <assert.h>

#include "C:/Users/Kalle13/CppWorkspace/SFML/Game_Engine/Entity/Entity.h"
#include "LevelTile.h"
#include "TileFactory.h"

class Level : public sf::Drawable
{
public:

   Level() : numberOfEntities(0), numberOfTiles(0), numberOfGateTiles(0) {};
   Level(unsigned initLevelNumber) : levelNumber(initLevelNumber), numberOfEntities(0), numberOfTiles(0) {}
   ~Level();

   unsigned    GetLevelNumber()           {return levelNumber;}
   unsigned    GetLevelNumberOfEntites()  {return numberOfEntities;}
   bool        GetEntityData(unsigned entityIndex, Entity &entity);
   //void      DeleteEntityData();  // Function to delete level entity data after it has been used by Game class to initialize entities (level does not need to store this information anymore)

   // Functions to change levels
   bool        ChangeLevel(unsigned nextLevelNumber);

   // Tile-related functions
   void        ToggleLevelTiles(sf::Vector2f entityPosition, bool useKeyPressed);
   bool        CheckLevelForWalls(sf::Vector2f entityPositionWithOffset);

public:

   TileFactory tileFactory;

private:

   unsigned       levelNumber;

private:

   unsigned       numberOfEntities;
   sf::Vector2f   *entityPositions;
   sf::Color      *entityColors;
   float          *entityRadii;
   _Entity::Type  *entityTypes;
   Entity         *levelEntities;

private:

   unsigned       numberOfTiles;                // Total number of tiles in level
   sf::Vector2f   *tilePositions;
   sf::Color      *tileColors1;
   sf::Color      *tileColors2;
   Tile::Type     *tileTypes;
   bool           *tileStates;
   LevelTile      **levelTiles;                 // Array of pointers for derived tile types (create array with 'new')

private:

   unsigned       numberOfSwitchTiles;
   unsigned       *switchTileIndexes;           // Tile indexes of the switch tiles
   unsigned       *numberOfSwitchedTiles;       // Total number of affected ("switched") tiles for each switch tile
   unsigned       **switchedTileIndexes;        // Switched tile indexes for all switch tiles (2D array)

private:

   unsigned       numberOfGateTiles;
   unsigned       *gateTileIndexes;             // Tile indexes of the gate tiles
   unsigned       *gateTileLevelDestinations;
   sf::Vector2f   *gateTilePositionDestinations;

private:

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      for(unsigned i=0;i<numberOfTiles;++i)
      {
         target.draw(*(levelTiles[i]));
      }
   }
};

#endif // _LEVEL_H_
