#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Mob.h"
#include "Item.h"

#define MAX_MOBS 3
#define MAX_ITEMS 3

class Room
{
  private:
    Player *p;
    int mob_size;
    int loot_size;
    Mob mobs[MAX_MOBS];
    Item loot[MAX_ITEMS];

  public:
    Room();


    void spawn_mobs();
//  void spawn_loot();

    void display_mobs();

//    ~Room();
};

Room::Room()
{
  spawn_mobs();
//  spawn_loot();
}

void Room::spawn_mobs()
{
  
  Mob tmp;
  this->mob_size = (rand() % MAX_MOBS ) + 1; 
  for (int i = 0; i < this->mob_size; i++)
  {
    tmp.morph_mob();
    mobs[i] = tmp;
  }
}

void Room::display_mobs()
{
  for (int i = 0; i < this->mob_size; i++)
  {
    mobs[i].print();
    cout << endl;
  }
}

//void Room::spawn_loot()
//{
//
//}
