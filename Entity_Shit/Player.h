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

using namespace std;

class Player : public Entity
{
  private:
    int max_hp;
    int max_mp;
    int max_shield;
    string player_race;
    string player_path;

  public:

    // Constructor
    Player(string race="Human", string path="Warrior", string name="[ ]", 
        int sp=0, int hp=0, int mp=0, int armor=0, int shield=0, int shield_armor=0,
        int base_attack = 0, int wallet=0 );

    // setters
    void setStats(string race="Human", 
        int sp=0, int hp=0, int mp=0, int armor=0, int shield=0, int shield_armor=0,
        int base_attack = 0, int wallet=0 );
    void setMaxHP(int m_hp);
    void setMaxMP(int m_mp);
    void setMaxShield(int m_s);
    void setRace(string race);
    void setPath(string path);

    
    // getters
    int getMaxHP();
    int getMaxMP();
    int getMaxShield();
    string getRace();
    string getPath();

    bool apply_race(int race_id);
    bool apply_path(int path_id);

    void restore();
};

//=======================================================================================================================

Player::Player(string race, string path, string name, 
        int sp, int hp, int mp, int armor, int shield, int shield_armor,
        int base_attack, int wallet) : Entity(name, sp, hp, mp, armor, shield, shield_armor, base_attack, wallet)
{
  this->max_hp = hp;
  this->max_mp = mp;
  this->max_shield = shield;
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
void Player::setMaxHP(int m_hp)     { this->max_hp = m_hp;      }
void Player::setMaxMP(int m_mp)     { this->max_mp = m_mp;      }
void Player::setMaxShield(int m_s) { this->max_shield = m_s;   }
void Player::setRace(string race)   { this->player_race = race; }
void Player::setPath(string path)   { this->player_path = path; }

// Getters
int Player::getMaxHP()       { return this->max_hp;      }
int Player::getMaxMP()       { return this->max_mp;      }
int Player::getMaxShield()   { return this->max_shield;  }
string Player::getRace()     { return this->player_race; }
string Player::getPath()     { return this->player_path; }


bool Player::apply_race(int race_id)
{

  ifstream race_file;
  race_file.open("race.csv");
  string value;
  bool id_found = false;
  int i = 0;
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

bool Player::apply_path(int path_id)
{

  ifstream path_file;
  path_file.open("path.csv");
  string value;
  int i = 0;
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


void Player::restore()
{
  this->hp     = this->max_hp;
  this->mp     = this->max_mp;
  this->shield = this->max_shield;  
}

