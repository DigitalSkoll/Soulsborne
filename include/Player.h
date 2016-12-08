//================================
//
//  Player Class
//
//  Derive of Entity Class
//
//================================
#pragma once
#include <fstream>
#include <stdlib.h>
#include "Entity.h"
#include "Mob.h"
#include "Role.h"

using namespace std;

class Player : public Entity
{
  private:
    string player_race;
    string player_path;


  public:

    // Constructor
    Player(string name="[ ]", string race="[ ]", string path="[ ]", 
        int sp=0, int hp=0, int mp=0, int armor=0, int shield=0, int shield_armor=0,
        int base_attack = 0, int wallet=0 );

    // setters
    void setStats(string race="[ ]", 
        int sp=0, int hp=0, int mp=0, int armor=0, int shield=0, int shield_armor=0,
        int base_attack = 0, int wallet=0 );
    void setRace(string race);
    void setPath(string path);

    
    // getters
    string getRace();
    string getPath();

    bool apply_race(int race_id);
    bool apply_path(int path_id);
    void loot_items(Mob &m);
    void loot_gear(Mob &m);
    void inven_mgmt();
    void gear_mgmt();

    void refresh();

};

//=======================================================================================================================

Player::Player(string name, string race, string path, 
        int sp, int hp, int mp, int armor, int shield, int shield_armor,
        int base_attack, int wallet) : Entity(name, sp, hp, mp, armor, shield, shield_armor, base_attack, wallet)
{
  this->player_race = race;
  this->player_path = path;
}

void Player::setStats(string race,
        int sp, int hp, int mp, int armor, int shield, int shield_armor,
        int base_attack, int wallet)
{
  this->player_race = race;
  Entity::setStats(sp, hp, mp, armor, shield, shield_armor, base_attack, wallet);
}

// Setters
void Player::setRace(string race)   { this->player_race = race; }
void Player::setPath(string path)   { this->player_path = path; }

// Getters
string Player::getRace()     { return this->player_race; }
string Player::getPath()     { return this->player_path; }


bool Player::apply_race(int race_id)
{
  if (races.empty())
  {
    cerr << "No Race\n";
    return false;
  }
  this->player_race   = races[race_id].name;
  this->hp            = races[race_id].hp;
  this->mp            = races[race_id].mp;
  this->armor         = races[race_id].armor;
  this->shield        = races[race_id].shield;  
  this->shield_armor  = races[race_id].shield_armor;  
  this->wallet        = races[race_id].wallet;
  this->base_attack   = races[race_id].attack;
  this->speed         = races[race_id].speed;

  return true;

}

bool Player::apply_path(int path_id)
{
  if (paths.empty())
  {
    cerr << "No Path\n";
    return false;
  }
  this->player_path    = paths[path_id].name;
  this->hp            += paths[path_id].hp;
  this->mp            += paths[path_id].mp;
  this->armor         += paths[path_id].armor;
  this->shield        += paths[path_id].shield;  
  this->shield_armor  += paths[path_id].shield_armor;  
  this->wallet        += paths[path_id].wallet;
  this->base_attack   += paths[path_id].attack;
  this->speed         += paths[path_id].speed;

  return true;
}

void Player::refresh()
{
  this->hp     = this->max_hp;
  this->mp     = this->max_mp;
  this->shield = this->max_shield;
}

void Player::loot_items(Mob &m)
{
  if (m.is_dead())
  {
    for(int i = 0; i < m.num_inven(); i++)
   {
     this->add_item(m.get_item(i));
     cout << "Got: " << m.get_item_name(i) << endl;; 
     m.remove_item(i);
   }
  }
  else
    cout << "It is Still Alive!\n";
}

void Player::loot_gear(Mob &m)
{
  if (m.is_dead())
  {
    for(int i = 0; i < m.num_inven(); i++)
   {
     this->add_gear(m.get_gear(i));
     cout << "Got: " << m.get_gear_name(i) << endl;
   }
  }
  else
    cout << "It is Still Alive!\n";
}

void Player::inven_mgmt()
{
  string resp;
  int i;
  while (true)
  {
    cout << "inventory ~> ";
    getline(cin, resp);

    if ("print" == resp)
      this->print_all_inven();
    else if ("use" == resp)
    {
      cout << "inventory ~> item id ] ";
      cin >> i;
      cin.clear();
      cin.ignore();
      this->use_item(i);
    }
    else if ("detail" == resp)
    {
      cout << "inventory ~> item id ] ";
      cin >> i;
      cin.clear();
      cin.ignore();
      this->print_inven(i);
    }
    else if ("drop" == resp)
    {
      cout << "inventory ~> item id ] ";
      cin >> i;
      cin.clear();
      cin.ignore();
      this->remove_item(i);
    }
    else if ("num" == resp)
    {
      cout << this->num_inven() << " in Inventory\n";
    }
    else if ("help" == resp)
    {
      cout << "print  - print list of items in inventory\n"
           << "use    - use an item\n"
           << "detail - see detailed information about item\n"
           << "drop   - drop an item\n"
           << "num    - total number of items in inventory\n"
           << "quit   - exit mgmt\n"
           << "help   - print this message\n";
    }
    else if ("quit" == resp)
      break;
    else
      cout << "Invalid command\n";
  }
}

void Player::gear_mgmt()
{
  string resp;
  int i;
  char loc;
  while (true)
  {
    cout << "gear ~> ";
    getline(cin, resp);

    if ("print" == resp)
      this->print_all_gear();
    else if ("put_on" == resp)
    {
      cout << "gear ~> gear id ] ";
      cin >> i;
      cin.clear();
      cin.ignore();
      cout << "gear ~> gear id ] wear } ";
      cin >> loc;
      cin.clear();
      cin.ignore();
      put_on(loc, gear[i]);
    }
    else if ("take_off" == resp)
    {
      cout << "gear ~> wear ] ";
      cin >> loc;
      cin.clear();
      cin.ignore();
      take_off(loc);
    }
    else if ("equip" == resp)
    {
      this->print_equip();
    }
    else if ("detail" == resp)
    {
      cout << "gear ~> gear id ] ";
      cin >> i;
      cin.clear();
      cin.ignore();
      this->print_gear(i); 
    }
    else if ("drop" == resp)
    {
      cout << "gear ~> gear id ] ";
      cin >> i;
      cin.clear();
      cin.ignore();
      this->remove_gear(i);
    }
    else if ("num" == resp)
    {
      cout << this->num_gear() << " in Inventory\n";
    }
    else if ("help" == resp)
    {
      cout << "print    - print list of gear in inventory\n"
           << "put_on   - put gear on\n"
           << "take_off - take gear off\n"
           << "equip    - print equiped gear\n"
           << "detail   - see detailed information about gear\n"
           << "drop     - drop gear\n"
           << "num      - total number of gear in inventory\n"
           << "quit     - exit mgmt\n"
           << "help     - print this message\n";
    }
    else if ("quit" == resp)
      break;
    else
      cout << "Invalid command\n";
  }
}
