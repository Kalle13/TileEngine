#ifndef _LEVEL_TILE_H_
#define _LEVEL_TILE_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

#define TILE_WIDTH 32
#define TILE_HEIGHT 32


namespace Tile
{
   enum Type{Base, Wall, Gate, Switch};
}


class LevelTile : public sf::Drawable{
public:

   LevelTile(unsigned initTileIndex, sf::Vector2f initTilePosition, Tile::Type initTileType,
             sf::Color initTileColor1, sf::Color initTileColor2) :
                tileIndex(initTileIndex),
                tilePosition(initTilePosition),
                tileType(initTileType),
                tileColor1(initTileColor1),
                tileColor2(initTileColor2)
   {
      tileRectangle.setSize(sf::Vector2f(TILE_WIDTH,TILE_HEIGHT));
      tileRectangle.setFillColor(initTileColor1);
      tileRectangle.setOrigin(TILE_WIDTH/2,TILE_HEIGHT/2);
      tileRectangle.setPosition(initTilePosition);
   }
   virtual ~LevelTile() {};
   void           SetTileColors(sf::Color newTileColor1, sf::Color newTileColor2);
   void           SetTilePosition(sf::Vector2f newTilePosition);
   void           UpdateTileRectangle(sf::Vector2f newPosition, sf::Color newColor);
   void           UpdateTileRectangleColor(sf::Color newRectColor);
   void           ToggleTileColor();

   sf::Color      GetTileColor1()      {return tileColor1;}
   sf::Color      GetTileColor2()      {return tileColor2;}
   sf::Vector2f   GetTilePosition()    {return tilePosition;}

   bool           TestVectorCollision(sf::Vector2f testVector);
   bool           TestRectangleCollision(sf::FloatRect floatRect);

   Tile::Type     GetTileType()        {return tileType;}
   virtual void   UpdateTile() = 0;

protected:

   unsigned             tileIndex;     // Tile index helpful for when tiles need to act upon one another
   sf::Vector2f         tilePosition;
   Tile::Type           tileType;
   sf::Color            tileColor1;
   sf::Color            tileColor2;
   sf::RectangleShape   tileRectangle;

private:

   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(tileRectangle);
   }
};


class BaseTile : public LevelTile{
public:

   BaseTile(unsigned initTileIndex, sf::Vector2f initTilePosition,
            sf::Color initTileColor1, sf::Color initTileColor2) :
            LevelTile(initTileIndex, initTilePosition, Tile::Base, initTileColor1, initTileColor2)
   {}
   //Tile::Type GetTileType() override {return Tile::Type::Base;}
   void UpdateTile() override;

};


class WallTile : public LevelTile{
public:

   WallTile(unsigned initTileIndex, sf::Vector2f initTilePosition,
            sf::Color initTileColor1, sf::Color initTileColor2,
            bool wallTileEnabled) :
               LevelTile(initTileIndex, initTilePosition, Tile::Wall, initTileColor1, initTileColor2),
               wallEnabled(wallTileEnabled)
   {}
   //Tile::Type GetTileType() override {return Tile::Type::Wall;}
   void UpdateTile() override;

   bool GetWallState(){return wallEnabled;}
   void SetWallState(bool setWallEnabled){wallEnabled = setWallEnabled;}    // Used to enable/disable a wall from a switch
   void ToggleWallState();

private:

   bool wallEnabled;

};


class GateTile : public LevelTile{
public:

   GateTile(unsigned initTileIndex, sf::Vector2f initTilePosition,
            sf::Color initTileColor1, sf::Color initTileColor2,
            bool initGateState) :
               LevelTile(initTileIndex, initTilePosition, Tile::Gate, initTileColor1, initTileColor2),
               gateOpen(initGateState)
   {}
   //Tile::Type   GetTileType() override {return Tile::Type::Gate;}
   void           UpdateTile() override;

   bool           GetGateState()             {return gateOpen;}
   unsigned       GetLevelDestination()      {return levelDestination;}          // Returns level number of gate destination (for inter-level gates)
   sf::Vector2f   GetLocationDestination()   {return locationDestination;}       // Returns position of gate destination (for intra-level gates)

   void           SetGateState(bool gateIsOpen)                      {gateOpen = gateIsOpen;}
   void           SetLevelDestination(unsigned newLevel)             {levelDestination = newLevel;}
   void           SetLocationDestination(sf::Vector2f newLocation)   {locationDestination = newLocation;}
   void           ToggleGateState();

private:

   unsigned       levelDestination;          // Level to send player (can be same as current level number if gate "warps" player)
   bool           gateOpen;
   sf::Vector2f   locationDestination;       // Location in level to send player

};


class SwitchTile : public LevelTile{
public:

   SwitchTile(unsigned initTileIndex, sf::Vector2f initTilePosition,
              sf::Color initTileColor1, sf::Color initTileColor2,
              bool initSwitchState) :
                 LevelTile(initTileIndex, initTilePosition, Tile::Gate, initTileColor1, initTileColor2),
                 switchState(initSwitchState)
   {}
   ~SwitchTile(){delete[] switchedTileIndexes;}
   //Tile::Type GetTileType() override {return Tile::Type::Switch;}
   void        UpdateTile() override;

   void        SetSwitchState(bool switchState);
   void        SetSwitchedTileIndexes(unsigned *tileIndexArray, unsigned numTileIndexes);
   bool        GetSwitchState(){return switchState;}
   void        ToggleSwitchState();

private:

   unsigned    numSwitchedTiles;
   bool        switchState;
   unsigned    *switchedTileIndexes;   // Tile indexes can correspond to Wall, Gate, or other Switch tiles to turn a Wall off, open/close a gate, or toggle another switch

};

#endif // _LEVEL_TILE_H_
