#ifndef _LEVEL_DATA_H_
#define _LEVEL_DATA_H_

#include "LevelTile.h"

struct TileData
{
   Tile::Type tileType;
   sf::Vector2f tilePosition;
   sf::Color tileColor;
};

class LevelData
{
public:

   LevelData();
   ~LevelData(){delete[] tileData;}

   SetLevelData
   sf::Vector2f GetTilePositions(unsigned tileIndex);
   sf::Color GetTileColors(unsigned tileIndex);

private:

   unsigned levelNumber;
   sf::Vector2f

};

unsigned GetBasicLevelData(unsigned levelNumber)
{
   switch(levelNumber)
   {
   case 0:
      return 25;
   case 1:
      return 36:
   case 3:
      return 49;
   default:
      return 0;
   }
}


void GetLevelData(unsigned levelNumber, unsigned *numTiles, sf::Vector2f *tilePositions, sf::Color *tileColors, LevelTile **levelTiles)
{
   switch(levelNumber)
   {
   case 0:
      *numTiles = 25;
      tilePosition
      for(unsigned i=0;i<*numTiles;++i){

      }
      break;
   }
}

#endif // _LEVEL_DATA_H_
