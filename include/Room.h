#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Player.h"
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
    Mob mobs[MAX_MOBS];
    Item loot[MAX_ITEMS];
    Room * doors[NUM_DOORS];
    Room * previous;
    Room * next;

  public:
    Room(Player soul);

    void add_player(Player soul);
    void remove_player();

    void spawn_mobs();
    void spawn_loot();

    ~Room();
};

Room::Room(Player soul)
{
  this->p        = &soul;
  this->previous = NULL;
  this->next     = NULL;
  for (int i = 0; i < NUM_DOORS; i++)
  {
    doors[i] = NULL;
  }
  spawn_mobs();
  spawn_loot();
}

void Room::add_player(Player soul) { this->p = &soul; }
void Room::remove_player()         { this->p = NULL;  }

void Room::spawn_mobs()
{
//  int num = (rand() % MAX_MOBS ) + 1; // unused according to g++
}

void Room::spawn_loot()
{

}

Room::~Room()
{

}
