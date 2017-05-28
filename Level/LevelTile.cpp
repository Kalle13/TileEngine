#include "LevelTile.h"

void LevelTile::UpdateTileRectangle()
{
   tileRectangle.setSize(sf::Vector2f(TILE_WIDTH,TILE_HEIGHT));
   tileRectangle.setFillColor(tileColor);
   tileRectangle.setOrigin(TILE_WIDTH/2,TILE_HEIGHT/2);
   tileRectangle.setPosition(tilePosition);
}


void LevelTile::SetTileColors(sf::Color newTileColor1, sf::Color newTileColor2)
{
   tileColor1 = newTileColor1;
   tileColor2 = newTileColor2;
   UpdateTileRectangleColor();
}


void LevelTile::SetTilePosition(sf::Vector2f newTilePosition)
{
   tilePosition = newTilePosition;
}


void LevelTile::UpdateTileRectangleColor(sf::Color newRectColor)
{
   tileRectangle.setFillColor(newRectColor);
}


bool LevelTile::TestVectorCollision(sf::Vector2f testVector)
{
   return tileRectangle.getGlobalBounds().contains(testVector);
}


bool LevelTile::TestRectangleCollision(sf::FloatRect floatRect)
{
   return tileRectangle.getGlobalBounds().intersects(floatRect);
}


void BaseTile::UpdateTile()
{
   if(entityCollisionFlag){
      UpdateTileRectangle(tileColor1);
   } else {
      UpdateTileRectangle(tileColor2);
   }
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
