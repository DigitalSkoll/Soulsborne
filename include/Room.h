#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Player.h"
#include "Mob.h"
#include "Item.h"

#define MAX_MOBS 3
#define MAX_ITEMS 3

class Room
{
  private:
    Player *p;
    Mob mobs[MAX_MOBS];
    Item loot[MAX_ITEMS];

  public:
    Room(Player soul = NULL);

    void add_player(Player soul);
    void remove_player();

    void spawn_mobs();
    void spawn_loot();

    ~Room();
};

Room::Room(Player soul)
{
  this->p = &soul;
  spawn_mobs();
  spawn_loot();
}

void Room::add_player(Player soul) { this->s = &soul; }
void Room::remove_player()         { this->s = NULL;  }

void spawn_mobs()
{
  int num = (rand() % MAX_MOBS ) + 1;
}
