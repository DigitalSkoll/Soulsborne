#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct race
{
  int id;
  string name;
  int speed;
  int hp;
  int mp;
  int armor;
  int shield;
  int shield_armor;
  int wallet;

  bool load_race(int race_id);
};

bool race::load_race(int race_id)
{
  fstream in("race.csv");
  string line;

  getline("


}
