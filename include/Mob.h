//================================
//
//  Mob Class
//
//  Derive of Entity Class
//
//================================
#pragma once
#include <fstream>
#include <stdlib.h>
#include "Entity.h"

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
    void print();

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

  ifstream race_file;
  race_file.open("../data/race.csv");
  string value;
  bool id_found = false;
//  int i = 0; // unused according to g++
  string race;

  while(getline(race_file, value,','))
  {
    if (value == to_string(race_id))
    {
      id_found = true;
      // get race
      getline(race_file, race,',');
      this->mob_race = race,
      // get speed
      getline(race_file, value, ',');
      this->speed = atoi(value.c_str());
      // get hp
      getline(race_file, value, ',');
      this->hp = atoi(value.c_str());
      // get mp
      getline(race_file, value, ',');
      this->mp = atoi(value.c_str());
      // get wallet 
      getline(race_file, value, ',');
      this->wallet = atoi(value.c_str());
      // get armor 
      getline(race_file, value, ',');
      this->armor = atoi(value.c_str());
      // get shield 
      getline(race_file, value, ',');
      this->shield = atoi(value.c_str());
      // get shield armor 
      getline(race_file, value, ',');
      this->shield_armor = atoi(value.c_str());
      // get base attack 
      getline(race_file, value, ',');
      this->base_attack = atoi(value.c_str());
    }
    else
      getline(race_file, value);
  }

  race_file.close();

  return id_found;

}

bool Mob::apply_path(int path_id)
{

  ifstream path_file;
  path_file.open("../data/path.csv");
  string value;
//  int i = 0; // unused according to g++
  string path;
  bool id_found = false;

  while(getline(path_file, value,','))
  {
    if (value == to_string(path_id))
    {
      id_found = true;
      // get path
      getline(path_file, path,',');
      this->mob_path = path;
      // get speed 
      getline(path_file, value, ',');
      this->speed += atoi(value.c_str());
      // get hp
      getline(path_file, value, ',');
      this->hp += atoi(value.c_str());
      // get mp
      getline(path_file, value, ',');
      this->mp += atoi(value.c_str());
      // get wallet 
      getline(path_file, value, ',');
      this->wallet += atoi(value.c_str());
      // get armor 
      getline(path_file, value, ',');
      this->armor += atoi(value.c_str());
      // get shield 
      getline(path_file, value, ',');
      this->shield += atoi(value.c_str());
      // get shield armor 
      getline(path_file, value, ',');
      this->shield_armor += atoi(value.c_str());
      // get base attack 
      getline(path_file, value, ',');
      this->base_attack += atoi(value.c_str());
    }
    else
      getline(path_file, value);
  }

  path_file.close();

  return id_found;
}

void Mob::print()
{
  cout << this->mob_race << " " << this->mob_path << endl;
}

void Mob::morph_mob()
{
  int rand_race = (rand() % 5) + 1;
  int rand_path = (rand() % 2) + 1;

  this->apply_race(rand_race);
  this->apply_path(rand_path);
}
