#ifndef _TILE_FACTORY_H_
#define _TILE_FACTORY_H_

#include "LevelTile.h"

class TileFactory
{
public:

   LevelTile GetLevelTile(Tile::Type tileType, unsigned tileIndex, sf:Vector2f initPosition, sf::Color initTileColor1, sf::Color initTileColor2,  bool initTileState)
   {
      switch(tileType)
      {
      case Tile::Base:
         BaseTile baseTile(initPosition,tileIndex);
         baseTile.SetTileColors(initTileColor1,initTileColor2);
         baseTile.UpdateTileRectangle();
         return baseTile;
      case Tile::Wall:
         WallTile wallTile(initPosition,tileIndex,initTileState);
         wallTile.SetWallColors(initTileColor1,initTileColor2);
         wallTile.UpdateTileRectangle();
         return wallTile;
      case Tile::Gate:
         GateTile gateTile(initPosition,tileIndex,initTileState);
         gateTile.SetGateColors(initTileColor1,initTileColor2);
         gateTile.UpdateTileRectangle();
         return gateTile;
      case Tile::Switch:
         SwitchTile switchTile(initPosition,tileIndex,initTileState);
         switchTile.SetSwitchColors(initTileColor1,initTileColor2);
         switchTile.UpdateTileRectangle();
         return switchTile;
      default:
         break;
      }
   }

};

#endif // _TILE_FACTORY_H_
