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
#include "LevelData.h"

class Level : public sf::Drawable
{
public:

   Level(unsigned initLevelNumber) : levelNumber(initLevelNumber), numberOfTiles(0) {}
   ~Level()
   {
      delete[] tilePositions;
      delete[] tileColors;
      delete[] tileTypes;
      delete[] levelTiles;
   }
   bool SetLevelNumber(unsigned newLevelNumber);
   unsigned GetLevelNumber(){return levelNumber;}

   // Functions to run after changing level number
   bool InitializeLevel();
   bool GetTilePositions();
   bool GetTileTypes();
   bool GetTileColors();

private:

   unsigned levelNumber;
   unsigned numberOfTiles;
   sf::Vector2f *tilePositions;
   sf::Color *tileColors;
   Tile::Type *tileTypes;
   LevelTile **levelTiles; // Array of pointers for derived tile types (create array with 'new')

private:

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      for(unsigned i=0;i<numberOfTiles;++i)
      {
         target.draw(levelTiles[i]);
      }
   }

};

#endif // _LEVEL_H_
