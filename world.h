#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

struct Block
{
  unsigned char id = 0;
  unsigned char state = 0;
};

class World
{
public:
    World();
    string name = "world";
    string description = "";
    int ticks = 20;
    string difficulty = "easy";
    bool hardcore = true;
    bool debug = false;
    bool log = false;

    int seed = 160;
    int gravity = 1;
    int seaLevel = 16;
    int seaDepth = 5;
    int mountainHeight = 32;
    bool structures = true;
    bool plants = true;
    bool animals = true;
    bool monsters = true;
    bool npcs = true;

    const static int width = 48;
    const static int height = 32;
    const static int depth = 32;
    Block* blocks[width][height][depth];

    void allocate();
    void generate();
    void load();
    void save();
    void update();
    vector<vector<Block>> getSlice(int x, int y, int z, int w, int h);
};

#endif
