#pragma once

#include "Direction.h"
#include "Map.h"
#include <utility>

typedef std::pair<int, int> iPair;

class Unit {
protected:
   iPair coordinates_;   // x & y
   bool isStarted_;      // is movement go on
   direction vector_;
   
   void changeCoordinates(iPair coordinates);
   void changeVector(direction move);

   iPair vector2Pair(direction vector);
   iPair sumCoordinates(iPair coordinates, iPair vector);

public:
   virtual void Init() = 0;
   virtual ~Unit() {};

   virtual void Movement(Map *map) = 0;
   void Show(char object);

   iPair getCoordinates();
   direction getVector();

   void changeIsStarted(bool started);
   bool getIsStarted();
};

iPair Unit::getCoordinates()
{
   return (*this).coordinates_;
}

direction Unit::getVector()
{
   return vector_;
}

void Unit::changeCoordinates(iPair coordinates)
{
   (*this).coordinates_.first = coordinates.first;
   (*this).coordinates_.second = coordinates.second;
}

void Unit::changeVector(direction move)
{
   (*this).vector_ = move;
}

iPair Unit::vector2Pair(direction vector)
{
   iPair temp = {0, 0};

   switch (vector) {
   case UP:
      temp.first = -1;
      break;
   case LEFT:
      temp.second = -1;
      break;
   case DOWN:
      temp.first = 1;
      break;
   case RIGHT:
      temp.second = 1;
      break;
   }

   return temp;
}

iPair Unit::sumCoordinates(iPair coordinates, iPair vector)
{
   coordinates.first += vector.first;
   coordinates.second += vector.second;

   return coordinates;
}

void Unit::Show(char object)
{
   COORD position;
   position.Y = coordinates_.first + 1;
   position.X = coordinates_.second;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
   std::cout << object;
}

void Unit::changeIsStarted(bool started)
{
   isStarted_ = started;
}

bool Unit::getIsStarted()
{
   return isStarted_;
}

