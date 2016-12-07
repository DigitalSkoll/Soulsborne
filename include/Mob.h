//================================
//
//  Mob Class
//
//  Derive of Entity Class
//
//================================
#pragma once
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Entity.h"
#include "Role.h"

using namespace std;

class Mob : public Entity
{
  private:
    string mob_race;
    string mob_path;

  public:

    // Constructor
    Mob(string race="Human", string path="Warrior", string name="[ ]",
        int sp=0, int hp=0, int mp=0, int armor=0, int shield=0, int shield_armor=0,
        int base_attack = 0, int wallet=0 );

    // setters
    void setStats(string race="Human",
        int sp=0, int hp=0, int mp=0, int armor=0, int shield=0, int shield_armor=0,
        int base_attack = 0, int wallet=0 );
    void setRace(string race);
    void setPath(string path);

    // getters
    string getRace();
    string getPath();

    bool apply_race(int race_id);
    bool apply_path(int path_id);
    void print_title();

    void morph_mob();
};

Mob::Mob(string race, string path, string name,
        int sp, int hp, int mp, int armor, int shield, int shield_armor,
        int base_attack, int wallet) : Entity(name, sp, hp, mp, armor, shield, shield_armor, base_attack, wallet)
{
  this->mob_race = race;
  this->mob_path = path;
}

void Mob::setStats(string race,
        int sp, int hp, int mp, int armor, int shield, int shield_armor,
        int base_attack, int wallet)
{
  this->mob_race = race;
  Entity::setStats(sp, hp, mp, armor, shield, shield_armor, base_attack, wallet);
}

void Mob::setRace(string race) { this->mob_race = race; }
void Mob::setPath(string path) { this->mob_path = path; }

string Mob::getRace() { return this->mob_race; }
string Mob::getPath() { return this->mob_path; }

bool Mob::apply_race(int race_id)
{
  if (races.empty())
  {
    cerr << "No Race\n";
    return false;
  }
  this->mob_race       = races[race_id].name;
  this->hp             = races[race_id].hp;
  this->mp             = races[race_id].mp;
  this->armor          = races[race_id].armor;
  this->shield         = races[race_id].shield;
  this->shield_armor   = races[race_id].shield_armor;
  this->wallet         = races[race_id].wallet;
  this->base_attack    = races[race_id].attack;
  this->speed          = races[race_id].speed;

  return true;
}

bool Mob::apply_path(int path_id)
{
  if (paths.empty())
  {
    cerr << "No Path\n";
    return false;
  }
  this->mob_path       = paths[path_id].name;
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

void Mob::print_title()
{
  cout << this->mob_race << " " << this->mob_path << endl;
}

void Mob::morph_mob()
{
  srand(time(NULL));
  // something is causing races.size() and probably paths.size() to be zero
  // this causes and arithmetic exception as % here attempts to divide by zero
//  int rand_race = (rand() % races.size()) + 1;
//  int rand_path = (rand() % paths.size()) + 1;
  int rand_race = 1;
  int rand_path = 1;

  this->apply_race(rand_race);
  this->apply_path(rand_path);
}
