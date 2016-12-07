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
