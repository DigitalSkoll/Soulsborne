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

enum fountain_status
{
  SUCC = 0,
  FAIL_EF, // empty fountain
  FAIL_NF  // no fountain
};

class Room
{
  friend class Map;
  private:
//  Player *p;
    bool locked;
    bool require_key;
    int fountain;
    unsigned int loot_size;
    unsigned int mob_size;
    vector<Item> loot;
    vector<Mob> mobs;
    Room * doors[NUM_DOORS];
    Room * previous;
    Room * next;
    room_type type;

  public:
//    Room(Player soul);
    Room(room_type t);
    fountain_status dec_fountain();
    bool start_combat(Player * p);
    int get_fountain() const;
    room_type get_type();
    unsigned int mob_alive_count();


    void spawn_boss();
    void spawn_mobs();
//  void spawn_loot();
    void loot_room(Player * p);

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
      this->fountain = -1;
      break;
    case SPAWN:
      this->fountain = 5;
      break;
    case BOSS:
      spawn_boss();
      this->fountain = -1;
      break;
    default:
      std::cout << "Something went terribly wrong in Room::Room(room_type t)\n";
  }
}

fountain_status Room::dec_fountain()
{
  if (this->fountain > 0)
  {
    fountain--;
    std::cout << "You feel refreshed\n";
    return SUCC;
  }
  else if (this->fountain == 0)
  {
    std::cout << "This fountain has run dry\n";
    return FAIL_EF;
  }
  else
  {
    std::cout << "You swallowed some air\n";
    return FAIL_NF;
  }

}

bool Room::start_combat(Player * p)
{
  // insert everything into the queue so that things faster than player
  // are in front and everything else is behind
  Queue<Entity *> combat_q([](Entity * a, Entity * b){ return b->get_speed() < a->get_speed(); });
  std::function<void()> load_queue = [& combat_q, this, & p]()
  {
    //unsigned int queue_size = this->mob_size + 1;
    unsigned int i = 0;
    std::vector<Mob>::iterator it;
    for (it = this->mobs.begin(); it != this->mobs.end(); it++, i++)
    {
      if (!it->is_dead())
      {
        combat_q.push(& (* it));
      }
    }

    combat_q.push(p);
/*
    for (i = 0; i < queue_size; i++)
    {
      std::cout << combat_q.front()->get_speed() << " - "
                << combat_q.front()->get_name() << std::endl;
      combat_q.pop();
    }
    */
  };

  std::string response;
  bool defending;
  while (!p->is_dead() && this->mob_alive_count() != 0)
  {
    defending = false;
    load_queue();
    while (!combat_q.is_empty())
    {
      if (combat_q.front() == p)
      {
        unsigned int i;
        while (true)
        {
          std::cout << "combat ~> ";
          getline(std::cin, response);
          if (response == "attack")
          {
            std::cout << "combat ~> mob id ] ";
            std::cin >> i;
            if (i >= this->mobs.size())
            {
              std::cout << "Invaild Index\n";
              std::cin.clear();
              std::cin.ignore();
            }
            else
            {
              std::cin.clear();
              std::cin.ignore();
              int dmg = p->attack();
              this->mobs.at(i).take_damage_hp(dmg);
              std::cout << "You did " << dmg << " damage to " << this->mobs.at(i).get_name() << "\n";
              break;
            }
          }
          else if (response == "defend")
          {
            defending = true;
            break;
          }
          if (response == "use")
          {
            std::cout << "combat/inventory ~> ";
            while (true)
            {
              getline(std::cin, response);
              if (response == "print")
              {
                p->print_all_inven();
              }
              else if (response == "detail")
              {
                std::cout << "combat/inventory ~> item id ] ";
                std::cin >> i;
                std::cin.clear();
                std::cin.ignore();
                p->print_inven(i);
              }
              else if (response == "stats")
              {
                p->print();
              }
              else if (response == "item")
              {
                std::cout << "combat/inventory ~> item id ] ";
                std::cin >> i;
                std::cin.clear();
                std::cin.ignore();
                p->use_item(i);
                break;
              }
              else if (response == "help")
              {
                std::cout << "print - print list of items in inventory\n"
                          << "detail - see detailed information about item\n"
                          << "stats - print your stats\n"
                          << "item - specify item to use\n"
                          << "cancel - cancel use item\n"
                          << "help - print this message\n";
              }
              else if (response == "cancel")
              {
                std::cout << "use item canceled\n";
                break;
              }
              else
              {
                std::cout << "I don't know how to \"" << response << "\"\n";
              }
            }
            break;
          }
          else if (response == "mobs")
          {
            this->display_mobs();
          }
          else if (response == "stats")
          {
            p->print();
          }
          else if (response == "end")
          {
            std::cout << "Turn ended without action\n";
            break;
          }
          else if (response == "help")
          {
            std::cout << "attack - attack an enemy\n"
                      << "defend - defend from enemy attack\n"
                      << "use - use an item\n"
                      << "mobs - show mobs\n"
                      << "stats - print your stats\n"
                      << "end - end your turn\n"
                      << "help - print this message\n";
          }
          else
          {
            std::cout << "I don't know how to \"" << response << "\"\n";
          }
        }
      }
      else
      {
        int dmg = combat_q.front()->attack();
        if (defending)
        {
          p->take_damage_shield(dmg);
          defending = false;
        }
        else
        {
          p->take_damage_hp(dmg);
        }
        std::cout << combat_q.front()->get_name() << " directed " << dmg << " damage toward you\n";
      }
      combat_q.pop();
    }
  }

  return p->is_dead();
}

int Room::get_fountain() const
{
  return this->fountain;
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

void Room::loot_room(Player * p)
{
  if (this->mobs.empty())
  {
    std::cout << "Cannot loot empty room\n";
  }
  else
  {
    unsigned int i;
    std::cout << "loot ~> mob id ] ";
    std::cin >> i;
    std::cin.clear();
    std::cin.ignore();
    if (i > this->mob_size)
    {
      std::cout << "That mob does not exist\n";
    }
    else
    {
      p->loot_items(this->mobs.at(i));
      p->loot_gear(this->mobs.at(i));
      this->mobs.at(i).remove_all_inven();
    }
  }
}

void Room::display_mobs()
{
  if (!this->mobs.empty())
  {
    for (unsigned int i = 0; i < this->mob_size; i++)
    {
      cout << i << ") ";
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
