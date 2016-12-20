//==========================================
// Entity Class
//
// Base class
// Marvin S. Leister
//==========================================

#pragma once
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Item.h"
#include "Equipment.h"

template <class A, class B>
using inventory = std::vector<std::pair<A, B>>;

class Entity
{
  protected:
    std::string name;               // Entity Name
    int speed;                      // speed 
    int hp;                         // Health Points
    int max_hp;                     // Max HP
    int mp;                         // Mana Points
    int max_mp;                     // Max MP
    int armor;                      // reduce incoming damage to hp by this amount
    int shield;                     // takes damage before health
    int max_shield;                 // Max Shield
    int shield_armor;               // reduce damage delt to shield
    int base_attack;                // basic damage delt
    int wallet;                     // Money
    bool dead;                      // alive or dead
    inventory<unsigned int, Item> list;              // Inventory
    inventory<unsigned int, Equipment> gear;         // Not used Gear
    Equipment left_hand;            // Equipment in Left Hand
    Equipment right_hand;           // Equipment in Right Hand
    Equipment body;                 // Equipment in Body

  public:
    // Constructors
    Entity(std::string n="[ ]", int sp=0, int h=0, int m=0, int a=0, int s=0, int sa=0, int ba=0, int money=0);

    void setStats(int sp, int h, int m, int a, int s, int sa, int ba, int money);

    // Getters
    std::string get_name();
    int get_speed();
    int get_hp();
    int get_mp();
    int get_armor();
    int get_shield();
    int get_shield_armor();
    int get_base_attack();
    bool is_dead();
    int get_wallet();

    // Setters
    void set_name(std::string n);
    void set_speed(int sp);
    void set_hp(int h);
    void set_mp(int m);
    void set_armor(int a);
    void set_shield(int s);
    void set_shield_armor(int sa);
    void set_base_attack(int ba);
    void set_dead(bool d);
    void set_wallet(int m);

    int attack();                                 // Entity returns attack
    void take_damage_shield(int d);               // Entity Shield takes damage
    void take_damage_hp(int d);                   // Entity HP takes damage
    void print();                                 // Print info
    void add_item(Item i);                       // Add Item to inventory
    Item get_item(unsigned int index);
    unsigned int get_item_count(unsigned int index);
    bool remove_item(unsigned int index);                  // Remove Item at index
    bool use_item(unsigned int index);                    // Apply item bonus to entity
    void print_inven(unsigned int i);                      // print iventory item at index i
    void print_inven(inventory<unsigned int, Item>::iterator& it); // print iventory item using iterator
    void print_all_inven();                       // print every item in inventory
    int num_inven();                              // print number of items in inventory
    int num_gear();
    int len_inven();
    int len_gear();
//  int inven_cost();                             // print total cost of items in inventory
    bool put_on(char pos, std::pair<unsigned int, Equipment> &eq);         // Put on eq at equip
    bool take_off(char pos);                      // Take off what is at equip

    void print_equip();
    void print_gear(unsigned int index);
    void print_gear(inventory<unsigned int, Equipment>::iterator& eq);
    void print_all_gear();
    void add_gear(Equipment eq);
    Equipment get_gear(unsigned int index);
    unsigned int get_gear_count(unsigned int index);
    bool remove_gear(unsigned int index);
    void remove_all_inven();

    string get_item_name(unsigned int index);
    string get_gear_name(unsigned int index);

};


// Constructors
Entity::Entity(std::string n, int sp, int h, int m, int a, int s, int sa, int ba, int money)
{
  this->name = n;
  this->speed = sp;
  this->hp = h;
  this->max_hp = this->hp;
  this->mp = m;
  this->max_mp = this->mp;
  this->armor = a;
  this->shield = s;
  this->max_shield = this->shield;
  this->shield_armor = sa;
  this->base_attack = ba;
  this->dead = false;
  this->wallet = money;
}

void Entity::setStats(int sp, int h, int m, int a, int s, int sa, int ba, int money)
{
  this->speed = sp;
  this->hp = h;
  this->mp = m;
  this->armor = a;
  this->shield = s;
  this->shield_armor = sa;
  this->base_attack = ba;
  this->wallet = money;
}

// Getters
std::string Entity::get_name() { return this->name; }
int Entity::get_speed() { return this->speed; }
int Entity::get_hp() { return this->hp; }
int Entity::get_mp() { return this->mp; }
int Entity::get_armor() { return this->armor; }
int Entity::get_shield() { return this->shield; }
int Entity::get_shield_armor() { return this->shield_armor; }
int Entity::get_base_attack() { return this->base_attack; }
bool Entity::is_dead() { return this->dead; }
int Entity::get_wallet() { return this->wallet; }

// Setters
void Entity::set_name(std::string n) { this->name = n; }
void Entity::set_speed(int sp) { this->speed = sp; }
void Entity::set_hp(int h) { this->hp = h; }
void Entity::set_mp(int m) { this->mp = m; }
void Entity::set_armor(int a) { this->armor = a; }
void Entity::set_shield(int s) { this->shield = s; }
void Entity::set_shield_armor(int sa) { this->shield_armor = sa; }
void Entity::set_base_attack(int ba) { this->base_attack = ba; }
void Entity::set_dead(bool d) { this->dead = d; }
void Entity::set_wallet(int m) { this->wallet = m; }

// attack()
// returns attack or returns 0 if the entity misses
// if the entity misses or not depends on a random number
// if the number is above 10 it is a hit
// if the number is below 10 it is a miss
int Entity::attack()
{

  int dice = rand()%20 + 1;
  if (dice >= 10)
    return this->base_attack;
  else
    return 0;
}

// take_damage_shield(int d)
// takes d as the damage delt and subtracts it from shield of the entity
// this will call take_damage_hp(int d) if shield is 0
void Entity::take_damage_shield(int d)
{
  int damage;
  if (this->shield <= 0)
    this->take_damage_hp(d);
  else
  {
    damage = d - this->shield_armor;
    if (damage < 0)
      damage = 0;
    this->shield -= damage;
    if (this->shield < 0)
    {
      damage = -1 * this->shield;
      this->shield = 0;
      this->take_damage_hp(damage);
    }

  }

}

// take_damage_hp(int d)
// takes d as the damage delt and subtracts it from health of the entity
// before return take_damage will test if player is dead or not
void Entity::take_damage_hp(int d)
{
  int damage;
  
  damage = d - this->armor;
  if (damage < 0)
     damage = 0;
  this->hp -= damage;
  if (this->hp <= 0)
    this->dead = true;
}

// print()
// print out basic info about the entity
void Entity::print()
{
  std::cout << "Name:         " << this->name << std::endl;
  std::cout << "Speed:        " << this->speed << std::endl;
  std::cout << "HP:           " << this->hp << std::endl;
  std::cout << "MP:           " << this->mp << std::endl;
  std::cout << "Wallet:       " << this->wallet << std::endl;
  std::cout << "Armor:        " << this->armor << std::endl;
  std::cout << "Shield:       " << this->shield << std::endl;
  std::cout << "Shield Armor: " << this->shield_armor << std::endl;
  std::cout << "Base Attack:  " << this->base_attack << std::endl;
  if (is_dead())
    std::cout << "Status:       Dead\n";
  else
    std::cout << "Status:       Alive\n";
}

// use_item(int index)
// apply the bonus of the item at index in list
bool Entity::use_item(unsigned int index)
{
  if (index >= this->list.size())
  {
    std::cout << "Invlaid index\n";
    return false;
  }

  this->hp     += list.at(index).second.get_hp_gain();
  this->mp     += list.at(index).second.get_mp_gain();
  this->shield += list.at(index).second.get_shield_gain();

  if(this->hp > this->max_hp)
  {
    this->hp = this->max_hp;
  }

  if (this->mp > this->max_mp)
  {
    this->mp = this->max_mp;
  }

  if (this->shield > this->max_shield)
  {
    this->shield = this->max_shield;
  }

  if (list.at(index).first > 1)
  {
    list.at(index).first--;
  }
  else
  {
    this->remove_item(index);
  }

  return true;
}
// add_item(Item i)
// test if the entity has enough money to buy the item
// if entity has enough subtract cost of item from wallet
// push item to the end of the vector and use the use_item(Item& i)
// function to apply armor and attack bonus from item to entity
void Entity::add_item(Item i)
{
  inventory<unsigned int, Item>::iterator it;
  bool added = false;
  for (it = list.begin(); it != list.end(); it++)
  {
    if ((* it).second == i)
    {
      (* it).first++;
      added = true;
    }
  }
  if (! added)
  {
    this->list.push_back(std::make_pair(1, i));
  }
}

Item Entity::get_item(unsigned int index)
{/*
  if (index >= list.size())
  {
    std::cout << "Invalid Index\n";
  }
*/
  return list.at(index).second;
}

unsigned int Entity::get_item_count(unsigned int index)
{/*
  if (index >= list.size())
  {
    std::cout << "Invalid Index\n";
  }
*/
  return list.at(index).first;
}

bool Entity::remove_item(unsigned int index)
{
  if (index >= list.size())
  {
    cout << "Invalid Index\n";
    return false;
  }

  if (list.at(index).first > 1)
  {
    list.at(index).first--;
  }
  else
  {
    this->list.erase(list.begin() + index);
  }

  return true;
}

// print_inven(int i)
// print item from inventory at index i
// use the print() function from Item object 
// to print out the item information
void Entity::print_inven(unsigned int i)
{
  if (i >= list.size())
    std::cout << "Invaid Index\n";
  else
    std::cout << i << ": " << list.at(i).second.get_name();

  if (list.at(i).first > 1)
  {
    std::cout << " (" << list[i].first << ")";
  }

  std::cout << std::endl;
}

// print_inven(inventory<unsigned int, Item>::iterator& it)
// same thing as print_inven(int i) except using 
// a vector iterator
void Entity::print_inven(inventory<unsigned int, Item>::iterator& it)
{
  std::cout << (it - list.begin()) + 1 << ": " << it->second.get_name();

  if (it->first > 1)
  {
    std::cout << " (" << it->first << ")";
  }

  std::cout << std::endl;
}

// print_all_inven()
// print all items in inventory using an iterator
// and print_inven(inventory<unsigned int, Item>::iterator& it)
void Entity::print_all_inven()
{
  inventory<unsigned int, Item>::iterator it;
  for (it =this->list.begin(); it < this->list.end(); it++)
    this->print_inven(it);
}

void Entity::print_gear(unsigned int index)
{
  if (index >= gear.size())
  {
    std::cout << "Invalid Index\n" << std::endl;
  }
  else
  {
    this->gear.at(index).second.print();
  }
}

// print gear
void Entity::print_gear(inventory<unsigned int, Equipment>::iterator& eq)
{
  cout << (eq - gear.begin()) + 1 << ": " << eq->second.get_name();

  if (eq->first > 1)
  {
    std::cout << " (" << eq->first << ")";
  }

  std::cout << std::endl;
}

// print_all_gear
void Entity::print_all_gear()
{
  inventory<unsigned int, Equipment>::iterator eq;
  for (eq =this->gear.begin(); eq < this->gear.end(); eq++)
    this->print_gear(eq);
}

// takes pointer to equipment and sets it to the address of eq
// if equip is not NULL the equipment must first be removed
// using the function take_off(Equipment *equip)
// if equip is NULL equip is set to address of eq and the 
// bonuses are applied to the Entity
bool Entity::put_on(char pos, std::pair<unsigned int, Equipment> &eq)
{
  Equipment *equip = NULL;
  switch (pos)
  {
    case 'l':
      equip = &this->left_hand;
      break;
    case 'r':
      equip = &this->right_hand;
      break;
    case 'b':
      equip = &this->body;
      break;
    default:
      cout << "Don't have that!\n";
      return false;
  }

  if (equip->get_name() != "[ ]")
  {
    cout << "You already have something there!\n";
    return false;
  }
  else
  {
    *equip = eq.second;

    this->base_attack  += equip->get_attack_bonus();
    this->shield       += equip->get_shield_bonus();
    this->max_shield   += equip->get_shield_bonus();
    this->armor        += equip->get_armor_bonus();
    this->shield_armor += equip->get_shield_armor_bonus();

    if (eq.first > 1)
    {
      eq.first--;
    }
    else
    {
      inventory<unsigned int, Equipment>::iterator it;

      for (it = gear.begin(); it != gear.end(); it++)
      {
        if (& (* it) == & eq)
        {
          gear.erase(it);
          break;
        }
      }
    }

    return true;
  }
}
// take_off(Equipment *equip)
// if equip is NULL return false
// if equip is not NULL, decrement stats
// by the bonus, set equip to NULL, and return true
bool Entity::take_off(char pos)
{
  Equipment *equip = NULL;
  switch (pos)
  {
    case 'l':
      equip = &this->left_hand;
      break;
    case 'r':
      equip = &this->right_hand;
      break;
    case 'b':
      equip = &this->body;
      break;
    default:
      cout << "Don't have that!\n";
      return false;
  }

  if (equip->get_name() == "[ ]")
  {
    cout << "Nothing is there!\n";
    return false;
  }
  else
  {
    this->base_attack  -= equip->get_attack_bonus();
    this->shield       -= equip->get_shield_bonus();
    this->max_shield   -= equip->get_shield_bonus();
    this->armor        -= equip->get_armor_bonus();
    this->shield_armor -= equip->get_shield_armor_bonus();

    bool added = false;
    inventory<unsigned int, Equipment>::iterator it;

    for (it = gear.begin(); it != gear.end(); it++)
    {
      if ((* it).second == * equip)
      {
        (* it).first++;
        added = true;
      }
    }
    if (! added)
    {
      this->add_gear(* equip);
    }

    Equipment tmp("[ ]");
    *equip = tmp;

    return true;
  }

}

int Entity::num_inven()
{
  unsigned int count;
  inventory<unsigned int, Item>::iterator it;

  for (it = list.begin(); it != list.end(); it++)
  {
    count += (* it).first;
  }

  return count;
}

int Entity::num_gear()
{
  unsigned int count;
  inventory<unsigned int, Item>::iterator it;

  for (it = list.begin(); it != list.end(); it++)
  {
    count += (* it).first;
  }

  return count;
}

int Entity::len_inven()
{
  return list.size();
}

int Entity::len_gear()
{
  return gear.size();
}

void Entity::print_equip()
{
  cout << "Right Hand :" << this->right_hand.get_name() << endl;
  cout << "Left Hand  :" << this->left_hand.get_name() << endl;
  cout << "Body       :" << this->body.get_name() << endl;
}

void Entity::add_gear(Equipment eq)
{
  inventory<unsigned int, Equipment>::iterator it;
  bool added = false;

  for (it = gear.begin(); it != gear.end(); it++)
  {
    if ((* it).second == eq)
    {
      (* it).first++;
      added = true;
    }
  }
  if (! added)
  {
    this->gear.push_back(std::make_pair(1, eq));
  }
}

Equipment Entity::get_gear(unsigned int index)
{/*
  if (index > list.size())
  {
    cout << "Invalid Index\n";
  }
*/
  return gear.at(index).second;
}

unsigned int Entity::get_gear_count(unsigned int index)
{/*
  if (index > list.size())
  {
    cout << "Invalid Index\n";
  }
*/
  return gear.at(index).first;
}

bool Entity::remove_gear(unsigned int index)
{
  if (index > gear.size())
  {
    cout << "Invalid Index\n";
    return false;
  }

  if (gear.at(index).first > 1)
  {
    gear.at(index).first--;
  }
  else
  {
    this->gear.erase(gear.begin() + index);
  }
  return true;
}

void Entity::remove_all_inven()
{
  this->list.clear();
  this->gear.clear();
}

string Entity::get_item_name(unsigned int index)
{
  return list.at(index).second.get_name();
}

string Entity::get_gear_name(unsigned int index)
{
  return gear.at(index).second.get_name();
}
