#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include "Item.h"
#include "Mob.h"
#include "Queue.h"

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
    unsigned int loot_size;
    unsigned int mob_size;
    vector<Item> loot;
    vector<Mob> mobs;
    Room * doors[NUM_DOORS];
    Room * previous;
    Room * next;
    room_type type;
    Queue<Entity *> combat_q;


  public:
//    Room(Player soul);
    Room(room_type t);
    bool start_combat(Player * p);
    room_type get_type();
    unsigned int mob_alive_count();


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

bool Room::start_combat(Player * p)
{
  // insert everything into the queue so that things faster than player
  // are in front and everything else is behind
  unsigned int order_size = this->mob_size + 1;
  std::vector<Entity *> order;
  unsigned int i = 0;
  std::vector<Mob>::iterator it;
  for (it = this->mobs.begin(); it != this->mobs.end(); it++, i++)
  {
    order.push_back(& (* it));
  }

  order.push_back(p);

  std::sort(order.begin(),
            order.end(),
            [](Entity * a, Entity * b){ return b->get_speed() < a->get_speed(); });

  for (i = 0; i < order_size; i++)
  {
    std::cout << order[i]->get_speed() << " - "
              << order[i]->get_name() << std::endl;
  }
/*
  while (!p->is_dead() || this->mobs_alive_count() != 0)
  {
    
  }
*/
  return p->is_dead();
}

room_type Room::get_type()
{
  return this->type;
}

unsigned int Room::mob_alive_count()
{
  unsigned int count = 0;

  if (!this->mobs.empty())
  {
    for (unsigned int i = 0; i < this->mob_size; i++)
    {
      if (!this->mobs.at(i).is_dead())
      {
        count++;
      }
    }
  }
  else
  {
    return 0;
  }

  return count;
}

void Room::spawn_boss()
{
  this->spawn_mobs();
}

void Room::spawn_mobs()
{
  Mob tmp;
  this->mob_size = (rand() % MAX_MOBS ) + 1;
  for (unsigned int i = 0; i < this->mob_size; i++)
  {
    tmp.morph_mob();
    mobs.push_back(tmp);
  }
}

void Room::display_mobs()
{
  if (!this->mobs.empty())
  {
    for (unsigned int i = 0; i < this->mob_size; i++)
    {
      cout << i << ") ",
      mobs.at(i).print();
      cout << endl;
    }
  }
  else
  {
    cout << "No mobs\n";
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
