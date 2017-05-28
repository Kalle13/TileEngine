#include "Level.h"

bool Level::SetLevelNumber(unsigned newLevelNumber)
{
   bool changeLevelSuccess = false;

   levelNumber = newLevelNumber;
   InitializeLevel();
}

bool Level::InitializeLevel()
{
   if(numberOfTiles>0){
      delete[] tilePositions;
      delete[] tileColors;
      delete[] tileTypes;
      delete[] levelTiles;
   }

   // Set level number
   switch(levelNumber)
   {
   case 0:
      numberOfTiles = 4;
      break;
   case 1:
      numberOfTiles = 25;
      break;
   case 2:
      numberOfTiles = 30;
      break;
   case 3:
      numberOfTiles = 36;
      break;
   default:
      numberOfTiles = 0;
      break;
   }

   // Allocate space for Level arrays
   tilePositions = new sf::Vector2f[numberOfTiles];
   tileColors = new sf::Color[numberOfTiles];
   tileTypes = new Tile::Type[numberOfTiles];
   levelTiles = new LevelTile*[numberOfTiles];

   bool tilePositionSuccess = GetTilePositions();
   bool tileTypeSuccess = GetTileTypes();
   bool tileColorSuccess = GetTileColors();

}


bool Level::GetTilePositions()
{
   if(numberOfTiles>0){
      switch(levelNumber)
      {
      case 0:
         tilePositions[0] = sf::Vector2(0,0);
         tilePositions[1] = sf::Vector2(32,0);
         tilePositions[2] = sf::Vector2(0,32);
         tilePositions[3] = sf::Vector2(32,32);
      default:
         break;
      }

      return true;
   } else {
      return false;
   }
}


bool Level::GetTileTypes()
{
   if(numberOfTiles>0){
      switch(levelNumber)
      {
      case 0:
         tileTypes[0] = Tile::Base;
         tileTypes[1] = Tile::Wall;
         tileTypes[2] = Tile::Switch;
         tileTypes[3] = Tile::Gate;
         break;
      default:
         break;
      }
      return true;
   } else {
      return false;
   }
}


bool Level::GetTileColors()
{
   if(numberOfTiles>0){
      switch(levelNumber)
      {
      case 0:
         tileColors[0] = sf::Color::Red;
         tileColors[1] = sf::Color::Yellow;
         tileColors[2] = sf::Color::Cyan;
         tileColors[3] = sf::Color::Blue;
         break;
      default:
         break;
      }
      return true;
   } else {
      return false;
   }
}
