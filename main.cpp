#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "world.h"

using namespace std;

bool running = true;
World* world;

int posX = 0;
int posY = 0;

void printSlice(int x, int y, int z, int w, int h)
{
  vector<vector<Block>> slice = world->getSlice(x, y, z, w, h);

  for (int i = h - 1; i > -1; i--)
  {
    for (int j = 0; j < w; j++)
    {
      mvprintw(i, j, "x");
      //cout << "\033[48;5;" + to_string(slice[j][i].id) + "m  ";
      //cout << "\u001b[4" + to_string(slice[j][i].id) + "m  \u001b[0m";
      //cout << to_string(slice[j][i].id);
    }
    //cout << endl;
  }
  //cout << "\u001b[0m";
}

int main(int argc, char *argv[])
{
  // Create a new world
  world = new World();
  cout << "Loading world..." << endl;
  world->load();
  cout << world->name << " loaded." << endl;

  int depth = 0;
  char input;

  // Init ncurses
  initscr();
  noecho();
  curs_set(FALSE);
  
  // Main game loop
  while (running)
  {
    //cout << "\033[2J\033[1;1H";

    //cout << "PIXELS" << endl << endl;

    clear();
    
    //printSlice(0, 0, depth, world->width, world->height);

    mvprintw(10, 10, "X");
    
    mvprintw(-posY + 30, posX, "O");
    
    refresh();
    
    //cin.ignore();
    //cin.get(input);

    //system("stty raw");
    input = getchar();
    //system("stty cooked");
    
    if (input == 'w')
      posY += 1;
    else if (input == 's')
      posY -= 1;
    else if (input == 'a')
      posX -= 1;
    else if (input == 'd')
      posX += 1;
    else if (input == 'q')
      running = false;
    
    world->generate();
  }

  endwin();
}
