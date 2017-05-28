#include "LevelTile.h"

void LevelTile::UpdateTileRectangle()
{
   tileRectangle.setSize(sf::Vector2f(TILE_WIDTH,TILE_HEIGHT));
   tileRectangle.setFillColor(tileColor);
   tileRectangle.setOrigin(TILE_WIDTH/2,TILE_HEIGHT/2);
   tileRectangle.setPosition(tilePosition);
}


void LevelTile::UpdateTileRectangleColor()
{
   tileRectangle.setFillColor(tileColor);
}


void BaseTile::UpdateTile()
{
   if(entityCollisionFlag){
      tileColor = entityCollisionColor;
   } else {
      tileColor = noEntityCollisionColor;
   }
   UpdateTileRectangleColor();
}


void WallTile::UpdateTile()
{
   if(wallEnabled){
      tileColor = wallEnabledColor;
   } else {
      tileColor = wallDisabledColor;
   }
   UpdateTileRectangleColor();
}


void GateTile::UpdateTile()
{
   if(gateOpen){
      tileColor = gateOpenColor;
   } else {
      tileColor = gateClosedColor;
   }
   UpdateTileRectangleColor();
}


void SwitchTile::UpdateTile()
{
   if(switchState){
      tileColor = switchColorOn;
   } else {
      tileColor = switchColorOff;
   }
   UpdateTileRectangleColor();
}

void SwitchTile::SetSwitchedTileIndexes(unsigned *tileIndexArray, unsigned numTileIndexes)
{
   switchedTileIndexes = new unsigned[numTileIndexes];

   for(unsigned i=0;i<numTileIndexes;++i){
      switchedTileIndexes[i] = tileIndexArray[i];
   }
}
