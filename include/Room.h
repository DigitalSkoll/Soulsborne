#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Mob.h"
#include "Item.h"

#define MAX_MOBS 3
#define MAX_ITEMS 3
#define NUM_DOORS 4

class Room
{
  friend class Map;
  private:
    Player *p;
    int mob_size;
    int loot_size;
    Mob mobs[MAX_MOBS];
    Item loot[MAX_ITEMS];
    Room * doors[NUM_DOORS];
    Room * previous;
    Room * next;

  public:
    Room();


    void spawn_mobs();
//  void spawn_loot();

    void display_mobs();

//    ~Room();
};

Room::Room()
{
<<<<<<< HEAD
=======
  this->p        = &soul;
  this->previous = NULL;
  this->next     = NULL;
  for (int i = 0; i < NUM_DOORS; i++)
  {
    doors[i] = NULL;
  }
>>>>>>> 00631e8b1662c8a37e9990f4e38f03897efbafc6
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

<<<<<<< HEAD
//void Room::spawn_loot()
//{
//
//}
=======
Room::~Room()
{

}
>>>>>>> 00631e8b1662c8a37e9990f4e38f03897efbafc6
