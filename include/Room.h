#pragma once
#include "Player.h"
#include "Mob.h"
#include "Item.h"
#include <iostream>
#include <string>
#include <cstdlib>
//#include "Map.h"

#define MAX_MOBS 3
#define MAX_ITEMS 3

class Room
{
  private:
    player *p;
    Mob mobs[MAX_MOBS];
    Item loot[MAX_ITEMS];

  public:
    Room(Player soul=NULL);

    void add_player(Player soul);
    void remove_player(Player soul);

    void spawn_mobs();
    void spawn_loot();

    void desc();

    ~Room();
};

Room::Room(Player soul)
{
  this->p = &soul;
  spawn_mobs();
  spawn_items();
}

void add_player(Player soul) { this->s = &soul; }
void remove_player(Player soul) { this->s = NULL; }

void spawn_mobs()
{
  int num = (rand() % MAX_MOBS) + 1;
  Mob mon;

  for (int i = 0; i < num; i++);
  {

  }
}
