#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <assert.h>

#include "LevelTile.h"
#include "TileFactory.h"

class Level : public sf::Drawable
{
public:

   Level() : numberOfTiles(0) {};
   Level(unsigned initLevelNumber) : levelNumber(initLevelNumber), numberOfTiles(0) {}
   ~Level();

   unsigned    GetLevelNumber(){return levelNumber;}

   // Functions to change levels
   bool        ChangeLevel(unsigned nextLevelNumber);

   // Tile-related functions
   void        LevelUpdateTiles(sf::Vector2f entityPosition, bool useKeyPressed);

public:

   TileFactory tileFactory;

private:

   unsigned       levelNumber;
   unsigned       numberOfTiles;                // Total number of tiles in level
   unsigned       numberOfSwitchTiles;          // Total number of switch tiles in level
   unsigned       *switchTileIndexes;           // Tile indexes of the switch tiles
   unsigned       *numberOfSwitchedTiles;       // Total number of affected ("switched") tiles for each switch tile
   unsigned       **switchedTileIndexes;        // Switched tile indexes for all switch tiles (2D array)
   sf::Vector2f   *tilePositions;
   sf::Color      *tileColors1;
   sf::Color      *tileColors2;
   Tile::Type     *tileTypes;
   bool           *tileStates;
   LevelTile      **levelTiles;                 // Array of pointers for derived tile types (create array with 'new')

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
