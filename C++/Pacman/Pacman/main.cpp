#include "User.h"
#include "NPC.h"

#include <conio.h>
#include <ctime>
#include <thread>

void Input(Pacman *pacman, bool *exit)
{
   while (true) {
      char button = _getch();
      pacman->changeIsStarted(TRUE);
      if (button == 27) {

         (*exit) = TRUE;
         return;
      }
      pacman->Control(button);
   }
}

void Out(Ghost *g2, Ghost *g3, Ghost *g4)
{
   Sleep(20000);
   g2->Show(' ');
   g2->Init();

   Sleep(20000);
   g3->Show(' ');
   g3->Init();

   Sleep(20000);
   g4->Show(' ');
   g4->Init();
}

void Game()
{
   Map map;
   Pacman pacman;
   pacman.Init();

   Ghost g1;
   g1.Init();
   Ghost g2;
   g2.otherInit(14, 11, DOWN);
   Ghost g3;
   g3.otherInit(13, 16, LEFT);
   Ghost g4;
   g4.otherInit(15, 14, UP);

   map.showMap();

   colorRed;
   g1.Show(g1.Appearence());
   g2.Show(g2.Appearence());
   g3.Show(g3.Appearence());
   g4.Show(g4.Appearence());
   map.changeObject(g1.getCoordinates(), g1.Appearence());
   map.changeObject(g2.getCoordinates(), g2.Appearence());
   map.changeObject(g3.getCoordinates(), g3.Appearence());
   map.changeObject(g4.getCoordinates(), g4.Appearence());

   colorYellow;
   pacman.Show(pacman.Direction());
   map.changeObject(pacman.getCoordinates(), pacman.Direction());

   map.hideCursor();

   bool exit = FALSE;
   std::thread thr(&Input, &pacman, &exit);
   std::thread ead(&Out, &g2, &g3, &g4);

   bool first1 = TRUE;
   bool first2 = TRUE;
   bool first3 = TRUE;
   bool first4 = TRUE;

   bool escape1 = FALSE;
   bool escape2 = FALSE;
   bool escape3 = FALSE;
   bool escape4 = FALSE;

   while (true) {
      while (true) {
         clock_t start, end;
         start = clock();

         if (pacman.getIsStarted() == TRUE) {
            pacman.Movement(&map);

            if (map.isEnergy() == TRUE) {
               g1.Energizer(&map, &first1, pacman, &escape1, 2, 2);
               g2.Energizer(&map, &first2, pacman, &escape2, 2, 23);
               g3.Energizer(&map, &first3, pacman, &escape3, 28, 2);
               g4.Energizer(&map, &first4, pacman, &escape4, 28, 23);
            } else {
               if (first1 == FALSE) {
                  first1 = TRUE;
                  escape1 = FALSE;
               }
               if (first2 == FALSE) {
                  first2 = TRUE;
                  escape2 = FALSE;
               }
               if (first3 == FALSE) {
                  first3 = TRUE;
                  escape3 = FALSE;
               }
               if (first4 == FALSE) {
                  first4 = TRUE;
                  escape4 = FALSE;
               }

               g1.LookAround(map, pacman.getCoordinates());
               g1.Movement(&map);
               if (map.isDead() == TRUE) {
                  g2.Show(' ');
                  g3.Show(' ');
                  g4.Show(' ');

                  map.changeObject(g2.getCoordinates(), ' ');
                  map.changeObject(g3.getCoordinates(), ' ');
                  map.changeObject(g4.getCoordinates(), ' ');

                  g2.otherInit(14, 11, DOWN);
                  g3.otherInit(13, 16, LEFT);
                  g4.otherInit(15, 14, UP);

                  std::thread ead(&Out, &g2, &g3, &g4);
               } else {

                  g2.LookAround(map, pacman.getCoordinates());
                  g2.Movement(&map);
                  g3.LookAround(map, pacman.getCoordinates());
                  g3.Movement(&map);
                  g4.LookAround(map, pacman.getCoordinates());
                  g4.Movement(&map);
               }
            }
         }

         if (exit == TRUE) {
            thr.detach();
            ead.detach();
            return;
         }
         
         do {
            end = clock();
         } while (0.2 - (float)(end - start) / CLOCKS_PER_SEC > 0);
      }
   }
   }

int main()
{
   Game();

   colorWhite;
   COORD position;
   position.Y = 34;
   position.X = 0;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

   system("pause");
   return 0;
}