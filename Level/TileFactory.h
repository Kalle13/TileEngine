#ifndef _TILE_FACTORY_H_
#define _TILE_FACTORY_H_
/*
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
*/
#include "LevelTile.h"

class TileFactory
{
public:

   LevelTile* GetLevelTile(Tile::Type tileType, unsigned tileIndex, sf::Vector2f initPosition, sf::Color initTileColor1, sf::Color initTileColor2,  bool initTileState)
   {
      switch(tileType)
      {
      case Tile::Base:
         return new BaseTile(tileIndex, initPosition, initTileColor1, initTileColor2);
      case Tile::Wall:
         return new WallTile(tileIndex, initPosition, initTileColor1, initTileColor2, initTileState);
      case Tile::Gate:
         return new GateTile(tileIndex, initPosition, initTileColor1, initTileColor2, initTileState);
      case Tile::Switch:
         return new SwitchTile(tileIndex, initPosition, initTileColor1, initTileColor2, initTileState);
      default:
         return new BaseTile(tileIndex, initPosition, initTileColor1, initTileColor2);
      }
   }

};

#endif // _TILE_FACTORY_H_
