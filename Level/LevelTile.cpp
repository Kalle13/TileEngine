#include "LevelTile.h"

void LevelTile::UpdateTileRectangle(sf::Vector2f newPosition, sf::Color newColor)
{
   tileRectangle.setSize(sf::Vector2f(TILE_WIDTH,TILE_HEIGHT));
   if(tileRectangle.getFillColor() == tileColor1){
      tileColor1 = newColor;
   } else {
      tileColor2 = newColor;
   }
   tileRectangle.setFillColor(newColor);
   tileRectangle.setOrigin(TILE_WIDTH/2,TILE_HEIGHT/2);
   tileRectangle.setPosition(tilePosition);
}

void LevelTile::SetTileColors(sf::Color newTileColor1, sf::Color newTileColor2)
{
   tileColor1 = newTileColor1;
   tileColor2 = newTileColor2;
   tileRectangle.setFillColor(tileColor1);
}

void LevelTile::SetTilePosition(sf::Vector2f newTilePosition)
{
   tilePosition = newTilePosition;
}

void LevelTile::UpdateTileRectangleColor(sf::Color newRectColor)
{
   tileRectangle.setFillColor(newRectColor);
}

void LevelTile::ToggleTileColor()
{
   if(tileRectangle.getFillColor() == tileColor1){
      tileRectangle.setFillColor(tileColor2);
   } else {
      tileRectangle.setFillColor(tileColor1);
   }
}

bool LevelTile::TestVectorCollision(sf::Vector2f testVector)
{
   return tileRectangle.getGlobalBounds().contains(testVector);
}

bool LevelTile::TestRectangleCollision(sf::FloatRect floatRect)
{
   return tileRectangle.getGlobalBounds().intersects(floatRect);
}

/*******************************  Base  Tile   *******************************/
void BaseTile::UpdateTile()
{
   if(tileRectangle.getFillColor() == tileColor1){
      tileRectangle.setFillColor(tileColor2);
   } else {
      tileRectangle.setFillColor(tileColor1);
   }
}

void BaseTile::ToggleTile()
{
   if(tileRectangle.getFillColor() == tileColor1){
      tileRectangle.setFillColor(tileColor2);
   } else {
      tileRectangle.setFillColor(tileColor1);
   }
}

bool BaseTile::GetTileState()
{
   return false;
}

/*******************************  Wall  Tile   *******************************/
void WallTile::UpdateTile()
{
   if(wallEnabled){
      UpdateTileRectangleColor(tileColor1);
   } else {
      UpdateTileRectangleColor(tileColor2);
   }
}

void WallTile::ToggleTile()
{
   ToggleWallState();
}

void WallTile::ToggleWallState()
{
   if(wallEnabled){
      wallEnabled = false;
   } else {
      wallEnabled = true;
   }
}

bool WallTile::GetTileState()
{
   return GetWallState();
}

/*******************************  Gate  Tile   *******************************/
void GateTile::UpdateTile()
{
   if(gateOpen){
      tileRectangle.setFillColor(tileColor1);
   } else {
      tileRectangle.setFillColor(tileColor2);
   }
}

void GateTile::ToggleTile()
{
   ToggleGateState();
}

void GateTile::ToggleGateState()
{
   if(gateOpen){
      gateOpen = false;
   } else {
      gateOpen = true;
   }
}

bool GateTile::GetTileState()
{
   return GetGateState();
}

/*******************************  Switch  Tile   *******************************/
void SwitchTile::UpdateTile()
{
   if(switchState){
      tileRectangle.setFillColor(tileColor1);
   } else {
      tileRectangle.setFillColor(tileColor2);
   }
}

void SwitchTile::ToggleTile()
{
   ToggleSwitchState();
}

void SwitchTile::SetSwitchedTileIndexes(unsigned *tileIndexArray, unsigned numTileIndexes)
{
   if(numSwitchedTiles>0){                // Delete old array of switched tile indexes first!
      delete[] switchedTileIndexes;
   }

   numSwitchedTiles = numTileIndexes;

   if(numSwitchedTiles>0){
      switchedTileIndexes = new unsigned[numSwitchedTiles];

      for(unsigned i=0;i<numSwitchedTiles;++i){
         switchedTileIndexes[i] = tileIndexArray[i];
      }
   }
}

void SwitchTile::ToggleSwitchState()
{
   if(switchState){
      switchState = false;
   } else {
      switchState = true;
   }
   //switchState != switchState;    // Does this work?
}

bool SwitchTile::GetTileState()
{
   return GetSwitchState();
}
