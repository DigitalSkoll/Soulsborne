#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#define RACE_FIELD 10
#define RACE "../data/Races.csv"

using namespace std;

struct race
{
  int id;
  string name;
  int hp;
  int mp;
  int armor;
  int shield;
  int shield_armor;
  int wallet;
  int attack;
  int speed;
};

vector<race> races;

void load_races(string file_name = RACE)
{
  ifstream race_in;
  race_in.open(file_name.c_str());
  string line;
  string field[RACE_FIELD];
  size_t pos;
  size_t start=0;
  int j = 0;
  race r;

  while (getline(race_in,line));
  {
    int j = 0;
    while (pos != string::npos && j < RACE_FIELD)
    {
      pos = line.find(',', start);
      field[j] = line.substr(start, pos - start);
      start = pos + 1;
      j++;
    }
    r.id           = atoi(field[0].c_str());
    r.name         = field[1];
    r.hp           = atoi(field[2].c_str());
    r.mp           = atoi(field[3].c_str());
    r.armor        = atoi(field[4].c_str());
    r.shield       = atoi(field[5].c_str());
    r.shield_armor = atoi(field[6].c_str());
    r.wallet       = atoi(field[7].c_str());
    r.attack       = atoi(field[8].c_str());
    r.speed        = atoi(field[9].c_str());
    races[r.id] = r;
  }
}
