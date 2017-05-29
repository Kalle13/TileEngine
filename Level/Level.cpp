#include "Level.h"

bool Level::UpdateLevel(unsigned nextLevelNumber)
{
   levelNumber = nextLevelNumber;

   if(numberOfTiles>0){
      delete[] tilePositions;
      delete[] tileColors1;
      delete[] tileColors2;
      delete[] tileTypes;
      delete[] tileStates;
      for(unsigned i=0;i<numberOfTiles;++i){
         delete levelTiles[i];
      }
      delete[] levelTiles;
   }

   // Set level number
   switch(levelNumber)
   {
   case 0:
      numberOfTiles = 4;
      break;
   default:
      numberOfTiles = 0;
      break;
   }

   // Allocate space for Level arrays
   tilePositions  = new sf::Vector2f[numberOfTiles];
   tileColors1    = new sf::Color[numberOfTiles];
   tileColors2    = new sf::Color[numberOfTiles];
   tileTypes      = new Tile::Type[numberOfTiles];
   tileStates     = new bool[numberOfTiles];
   levelTiles     = new LevelTile*[numberOfTiles];

   if(numberOfTiles>0){
      switch(levelNumber)
      {
      case 0:
         tilePositions[0] = sf::Vector2f(32,32);
         tilePositions[1] = sf::Vector2f(64,32);
         tilePositions[2] = sf::Vector2f(32,64);
         tilePositions[3] = sf::Vector2f(64,64);

         tileColors1[0] = sf::Color::Red;
         tileColors1[1] = sf::Color::Yellow;
         tileColors1[2] = sf::Color::Cyan;
         tileColors1[3] = sf::Color::Blue;

         tileColors2[0] = sf::Color::Green;
         tileColors2[1] = sf::Color(160,160,160);   // Grey?
         tileColors2[2] = sf::Color::Magenta;
         tileColors2[3] = sf::Color::White;

         tileTypes[0] = Tile::Base;
         tileTypes[1] = Tile::Wall;
         tileTypes[2] = Tile::Switch;
         tileTypes[3] = Tile::Gate;

         tileStates[0] = false;
         tileStates[1] = false;
         tileStates[2] = false;
         tileStates[3] = false;
         break;
      default:
         return false;
         break;
      }
   }

   for(unsigned i=0;i<numberOfTiles;++i){
      levelTiles[i] = tileFactory.GetLevelTile(tileTypes[i],i,tilePositions[i],tileColors1[i],tileColors2[i],tileStates[i]);
   }

   return true;
}

void Level::LevelUpdateTiles(sf::Vector2f entityPosition, bool useKeyPressed)
{

}
