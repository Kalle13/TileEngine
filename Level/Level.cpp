#include "Level.h"

Level::~Level()
{
   delete[] tilePositions;
   delete[] tileColors1;
   delete[] tileColors2;
   delete[] tileTypes;
   delete[] tileStates;
   for(unsigned i=0;i<numberOfTiles;++i){
      delete levelTiles[i];      // Delete pointers first
   }
   delete[] levelTiles;          // Delete array second

   for(unsigned i = 0;i<numberOfSwitchTiles;++i){
      delete[] switchedTileIndexes[i];
   }
   delete[] switchedTileIndexes;
   delete[] switchTileIndexes;
   delete[] numSwitchedTiles;       // Delete this after switchedTileIndexes 2D array
}

bool Level::ChangeLevel(unsigned nextLevelNumber)
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

      delete[] switchTileIndexes;
      delete[] numberOfSwitchedTiles;
      for(unsigned i = 0;i<numberOfSwitchTiles;++i){
         delete[] switchedTileIndexes[i];
      }
      delete[] switchedTileIndexes;

   }

   // Set level number
   switch(levelNumber)
   {
   case 0:
      numberOfTiles = 4;
      numberOfSwitchTiles = 1;
      break;
   default:
      numberOfTiles = 0;
      numberOfSwitchTiles = 0;
      break;
   }

   // Allocate space for Level arrays
   tilePositions  = new sf::Vector2f[numberOfTiles];
   tileColors1    = new sf::Color[numberOfTiles];
   tileColors2    = new sf::Color[numberOfTiles];
   tileTypes      = new Tile::Type[numberOfTiles];
   tileStates     = new bool[numberOfTiles];
   levelTiles     = new LevelTile*[numberOfTiles];

   switchTileIndexes       = new unsigned[numberOfSwitchTiles];
   numberOfSwitchedTiles   = new unsigned[numberOfSwitchTiles];
   switchedTileIndexes     = new unsigned*[numberOfSwitchTiles];

   if(numberOfTiles>0){
      switch(levelNumber)
      {
      case 0:
         tilePositions[0]  = sf::Vector2f(32,32);
         tilePositions[1]  = sf::Vector2f(64,32);
         tilePositions[2]  = sf::Vector2f(32,64);
         tilePositions[3]  = sf::Vector2f(64,64);

         tileColors1[0]    = sf::Color::Red;
         tileColors1[1]    = sf::Color::Yellow;
         tileColors1[2]    = sf::Color::Cyan;
         tileColors1[3]    = sf::Color::Blue;

         tileColors2[0]    = sf::Color::Green;
         tileColors2[1]    = sf::Color(160,160,160);   // Grey?
         tileColors2[2]    = sf::Color::Magenta;
         tileColors2[3]    = sf::Color::White;

         tileTypes[0]      = Tile::Base;
         tileTypes[1]      = Tile::Wall;
         tileTypes[2]      = Tile::Switch;
         tileTypes[3]      = Tile::Gate;

         tileStates[0]     = false;
         tileStates[1]     = false;
         tileStates[2]     = false;
         tileStates[3]     = false;

         switchTileIndexes[0]       = 2;                       // Because the tile with index=2 is a switch tile
         numberOfSwitchedTiles[0]   = 1;                       // Because the switch tile with index=2 will control 1 Gate tile

         {                                                     // New scope for tempSwitchedTileIndexes 2D array
            unsigned tempSwitchedTileIndexes[][] = {{3}};      // 2D array with index=3 of Gate tile that Switch tile with index=2 will control

            for(unsigned i=0;i<numberOfSwitchTiles;++i){
               switchedTileIndexes[i] = new unsigned[numberOfSwitchedTiles[i]];

               for(unsigned j=0;j<numberOfSwitchedTiles[i];++j){
                  switchTileIndexes[i][j] = tempSwitchedTileIndexes[i][j];
               }
            }
         }
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
   for(unsigned i=0;i<numberOfTiles;++i){
      if(levelTiles[i]->TestVectorCollision(entityPosition))
      {
         if(levelTiles[i]->GetTileType() == Tile::Switch && useKeyPressed){
            levelTiles[i]->ToggleTile();
         }
      }
   }
}
