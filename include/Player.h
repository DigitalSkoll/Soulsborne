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

#define RACE_FILE "../data/race.csv"
#define PATH_FILE "../data/path.csv"

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

  ifstream race_file;
  race_file.open(RACE_FILE);
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
      this->player_race = race,
      // get speed
      getline(race_file, value, ',');
      this->speed = atoi(value.c_str());
      // get hp
      getline(race_file, value, ',');
      this->hp = atoi(value.c_str());
      this->max_hp = this->hp;
      // get mp
      getline(race_file, value, ',');
      this->mp = atoi(value.c_str());
      this->max_mp = this->mp;
      // get wallet 
      getline(race_file, value, ',');
      this->wallet = atoi(value.c_str());
      // get armor 
      getline(race_file, value, ',');
      this->armor = atoi(value.c_str());
      // get shield 
      getline(race_file, value, ',');
      this->shield = atoi(value.c_str());
      this->max_shield = this->shield;
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

bool Player::apply_path(int path_id)
{

  ifstream path_file;
  path_file.open(PATH_FILE);
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
      this->player_path = path;
      // get speed 
      getline(path_file, value, ',');
      this->speed += atoi(value.c_str());
      // get hp
      getline(path_file, value, ',');
      this->hp += atoi(value.c_str());
      this->max_hp = this->hp;
      // get mp
      getline(path_file, value, ',');
      this->mp += atoi(value.c_str());
      this->max_mp = this->mp;
      // get wallet 
      getline(path_file, value, ',');
      this->wallet += atoi(value.c_str());
      // get armor 
      getline(path_file, value, ',');
      this->armor += atoi(value.c_str());
      // get shield 
      getline(path_file, value, ',');
      this->shield += atoi(value.c_str());
      this->max_shield = this->shield;
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
