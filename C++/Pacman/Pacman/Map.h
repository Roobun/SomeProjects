#pragma once

#include "Objects.h"
#include <iostream>
#include <utility>
#include <Windows.h>
#include <string>
#include <thread>

typedef std::pair<int, int> iPair;

class Map {
   #define Xmap 31
   #define Ymap 29

   bool pacmanIsDead_ = FALSE;
   bool energizer_ = FALSE;
   short lives_ = 3;

   int score_ = 0;
   int points_ = 0;

   char map[Xmap][Ymap] =
   {
      "############################",
      "#............##............#",
      "#.####.#####.##.#####.####.#",
      "#@####.#####.##.#####.####@#",
      "#.####.#####.##.#####.####.#",
      "#..........................#",
      "#.####.##.########.##.####.#",
      "#.####.##.########.##.####.#",
      "#......##....##....##......#",
      "######.##### ## #####.######",
      "     #.##### ## #####.#     ",
      "     #.##          ##.#     ",
      "     #.## ###//### ##.#     ",
      "######.## #      # ##.######",
      "      .   #      #   .      ",
      "######.## #      # ##.######",
      "     #.## ######## ##.#     ",
      "     #.##          ##.#     ",
      "     #.## ######## ##.#     ",
      "######.## ######## ##.######",
      "#............##............#",
      "#.####.#####.##.#####.####.#",
      "#.####.#####.##.#####.####.#",
      "#@..##................##..@#",
      "###.##.##.########.##.##.###",
      "###.##.##.########.##.##.###",
      "#......##....##....##......#",
      "#.##########.##.##########.#",
      "#.##########.##.##########.#",
      "#..........................#",
      "############################"
   };

   friend void EnergyBranch(Map *map);
      
public:
   void changeObject(iPair coordinates, char object);
   char getObject(int x, int y);

   void showMap();
   void hideCursor();
   void addPoints(int price);

   void Death();
   bool isDead();
   void PacmansDeath(bool yes);

   bool isEnergy();
   void Energy();

};

void Map::changeObject(iPair coordinates, char object)
{
   map[coordinates.first][coordinates.second] = object;
}

char Map::getObject(int x, int y)
{
   return map[x][y];
}

#define colorBlue    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE)
#define colorRed     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED)
#define colorYellow  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
#define colorWhite   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

void Map::showMap()
{
   colorWhite;
   COORD position;
   position.Y = 0;
   position.X = 0;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
   
   COORD crd = {50, 40};
   SMALL_RECT src = {0, 0, crd.X, crd.Y};
   SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), crd);
   SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &src);


   //Console::SetWindowSize(800, 800);
   std::cout << "Points: " << points_ << "    High Score: " << score_ << std::endl;

   for (int i = 0; i < Xmap; i++) {
      for (int j = 0; j < Ymap; j++) {
         if (map[i][j] == WALL) {
            colorBlue;
            std::cout << map[i][j];

         } else if (map[i][j] == GHOST) {
            colorRed;
            std::cout << map[i][j];

         } else if (map[i][j] == PACMAN_U || map[i][j] == PACMAN_L || 
                    map[i][j] == PACMAN_D || map[i][j] == PACMAN_R) {
            colorYellow;
            std::cout << map[i][j];

         } else {
            colorWhite;
            std::cout << map[i][j];
         }
      }
      std::cout << std::endl;
   }

   std::cout << "Lives: " << lives_ << std::endl;
}

void Map::hideCursor()
{
   void *handle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO structCursorInfo;
   GetConsoleCursorInfo(handle, &structCursorInfo);
   structCursorInfo.bVisible = FALSE;
   SetConsoleCursorInfo(handle, &structCursorInfo);
}

void Map::addPoints(int price)
{
   points_ += price;

   colorWhite;
   COORD position;
   position.Y = 0;
   position.X = 8;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
   std::cout << points_;

   if (points_ > score_) {
      score_ = points_;

      position.X = 25;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
      std::cout << score_;
   }
}

void Map::Death()
{
   lives_--;
   energizer_ = FALSE;

   colorWhite;
   COORD position;
   position.Y = 32;
   position.X = 7;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
   std::cout << lives_;
   
   points_ = 0;   
   position.Y = 0;
   position.X = 8;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
   std::cout << points_ << "   ";

   if (lives_ == 0) {
      system("cls");
      
      position.Y = 15;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
      std::cout << "Game over. Your score is " << score_ << std::endl;
      
      Sleep(1500);
      exit(1);
   }
}

bool Map::isDead()
{
   return pacmanIsDead_;
}

void Map::PacmansDeath(bool yes)
{
   pacmanIsDead_ = yes;
}

bool Map::isEnergy()
{
   return energizer_;
}

void EnergyBranch(Map *map)
{
   Sleep(7000);
   map->energizer_ = FALSE;
}

void Map::Energy()
{
   energizer_ = TRUE;
   std::thread tr(&EnergyBranch, this);
   tr.detach();
}
