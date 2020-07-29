#include "world.h"

World::World()
{
}

void World::allocate()
{
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      for (int z = 0; z < depth; z++)
      {
        Block* block = new Block();
        blocks[x][y][z] = block;
      }
    }
  }
}

void World::generate()
{
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      for (int z = 0; z < depth; z++)
      {
	blocks[x][y][z]->id = 1;
	blocks[x][y][z]->state = 0;
        //blocks[x][y][z]->id = rand() % 160 + 0;
	//blocks[x][y][z]->id = rand() % (y + 1) * 4;
        //blocks[x][y][z]->state = rand() % 5 + 0;
      }
    }
  }
}

void World::load()
{
  // Load settings
  ifstream file("world/world.yml");
  string line;
  srand(seed);
  
  if (file.good())
  {
    while (getline(file, line)) {
      if (line.length() > 1 && line[0] != '#')
      {
        string key = line.substr(0, line.find(": "));
        string value = line.substr(line.find(": ") + 2, line.length() - line.find(": ") - 3);
        if (key == "name")
          name = value;
        if (key == "seed")
          seed = stoi(value);
      }
    }
  }
  else
  {
    cout << "No world.yml settings file found." << endl;
  }

  // Check for world.dat
  ifstream f("world/world.dat", fstream::in);
  if (f.good())
  {
    cout << "Loading world.dat" << endl;
    char ch;
    allocate();
    for (int x = 0; x < width; x++)
    {
      for (int y = 0; y < height; y++)
      {
        for (int z = 0; z < depth; z++)
        {
          f >> noskipws >> ch;
          blocks[x][y][z]->id = ch;
          f >> noskipws >> ch;
          blocks[x][y][z]->state = ch;
        }
      }
    }
  }
  else
  {
    cout << "Generating new world." << endl;
    allocate();
    generate();
    save();
  }
}

void World::save()
{
  ofstream file("world/world.dat");

  if (file.fail()) return;

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      for (int z = 0; z < depth; z++)
      {
        file << blocks[x][y][z]->id << blocks[x][y][z]->state;
      }
    }
  }
}

void World::update()
{
}

vector<vector<Block>> World::getSlice(int _x, int _y, int z, int _w, int _h)
{
  vector<vector<Block>> slice;
  slice.resize(_w, vector<Block>(_h));

  for (int x = 0; x < _w; x++)
  {
    for (int y = 0; y < _h; y++)
    {
      slice[x][y].id = blocks[x + _x][y + _y][z]->id;
      slice[x][y].state = blocks[x + _x][y + _y][z]->state;
    }
  }

  return slice;
}
