#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "Item.h"
#include "Mob.h"

#define MAX_MOBS 3
#define MAX_ITEMS 3
#define NUM_DOORS 4

enum room_type
{
  NORMAL = 0,
  SPAWN,
  BOSS
};

class Room
{
  friend class Map;
  private:
//  Player *p;
    bool locked;
    bool require_key;
    int loot_size;
    int mob_size;
    Item loot[MAX_ITEMS];
    Mob mobs[MAX_MOBS];
    Room * doors[NUM_DOORS];
    Room * previous;
    Room * next;
    room_type type;


  public:
//    Room(Player soul);
    Room(room_type t);
    room_type get_type();

    void spawn_boss();
    void spawn_mobs();
//  void spawn_loot();

    void display_mobs();

//    ~Room();
};

//Room::Room(Player soul)
Room::Room(room_type t)
{
  this->type     = t;
  this->previous = NULL;
  this->next     = NULL;

  for (int i = 0; i < NUM_DOORS; i++)
  {
    doors[i] = NULL;
  }

  this->require_key = this->type == BOSS;
  this->locked      = this->type == BOSS;

  switch (t)
  {
    case NORMAL:
      spawn_mobs();
      break;
    case SPAWN:
      break;
    case BOSS:
      spawn_boss();
      break;
    default:
      std::cout << "Something went terribly wrong in Room::Room(room_type t)\n";
  }
}

room_type Room::get_type()
{
  return this->type;
}

void Room::spawn_boss()
{
  this->spawn_mobs();
}

void Room::spawn_mobs()
{
  srand(time(NULL));
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
    cout << i << ") ",
    mobs[i].print();
    cout << endl;
  }
}

//void Room::spawn_loot()
//{
//
//}
//Room::~Room()
//{
//
//}
