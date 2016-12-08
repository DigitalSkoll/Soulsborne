#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#define FIELD_RP 10
#define FIELD_I   5
#define FIELD_E   7

#define RACE  "data/Races.csv"
#define PATH  "data/Paths.csv"
#define ITEM  "data/Items.csv"
#define EQUIP "data/Equipment.csv"

using namespace std;

// Handle Races
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
  string field[FIELD_RP];
  size_t pos;
  size_t start;
  int j;
  race r;

  getline(race_in,line);

  while (getline(race_in,line))
  {
    j = 0;
    pos = 0;
    start = 0;
    while (pos != string::npos && j < FIELD_RP)
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
    races.push_back(r);
  }

  race_in.close();
}

// Handle Paths
struct path
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

vector<path> paths;

void load_paths(string file_name = PATH)
{
  ifstream path_in;
  path_in.open(file_name.c_str());
  string line;
  string field[FIELD_RP];
  size_t pos;
  size_t start;
  int j;
  path p;

  getline(path_in,line);

  while (getline(path_in,line))
  {
    j = 0;
    pos = 0;
    start = 0;
    while (pos != string::npos && j < FIELD_RP)
    {
      pos = line.find(',', start);
      field[j] = line.substr(start, pos - start);
      start = pos + 1;
      j++;
    }
    p.id           = atoi(field[0].c_str());
    p.name         = field[1];
    p.hp           = atoi(field[2].c_str());
    p.mp           = atoi(field[3].c_str());
    p.armor        = atoi(field[4].c_str());
    p.shield       = atoi(field[5].c_str());
    p.shield_armor = atoi(field[6].c_str());
    p.wallet       = atoi(field[7].c_str());
    p.attack       = atoi(field[8].c_str());
    p.speed        = atoi(field[9].c_str());
    paths.push_back(p);
  }

  path_in.close();
}

// Handle Items
struct item
{
  int id;
  string name;
  int hp;
  int mp;
  int shield;
};

vector<item> items;

void load_items(string file_name = ITEM)
{
  ifstream item_in;
  item_in.open(file_name.c_str());
  string line;
  string field[FIELD_I];
  size_t pos;
  size_t start;
  int j;
  item i;

  getline(item_in,line);

  while (getline(item_in,line))
  {
    j = 0;
    pos = 0;
    start = 0;
    while (pos != string::npos && j < FIELD_I)
    {
      pos = line.find(',', start);
      field[j] = line.substr(start, pos - start);
      start = pos + 1;
      j++;
    }
    i.id           = atoi(field[0].c_str());
    i.name         = field[1];
    i.hp           = atoi(field[2].c_str());
    i.mp           = atoi(field[3].c_str());
    i.shield       = atoi(field[4].c_str());
    items.push_back(i);
  }

  item_in.close();
}

// Handle Equipment
struct equip
{
  int id;
  string name;
  int attack;
  int armor;
  int shield;
  int shield_armor;
  int dur;
};

vector<equip> equips;

void load_equips(string file_name = EQUIP)
{
  ifstream equip_in;
  equip_in.open(file_name.c_str());
  string line;
  string field[FIELD_E];
  size_t pos;
  size_t start;
  int j;
  equip e;

  getline(equip_in,line);

  while (getline(equip_in,line))
  {
    j = 0;
    pos = 0;
    start = 0;
    while (pos != string::npos && j < FIELD_E)
    {
      pos = line.find(',', start);
      field[j] = line.substr(start, pos - start);
      start = pos + 1;
      j++;
    }
    e.id             = atoi(field[0].c_str());
    e.name           = field[1];
    e.attack         = atoi(field[2].c_str());
    e.armor          = atoi(field[3].c_str());
    e.shield         = atoi(field[4].c_str());
    e.shield_armor   = atoi(field[5].c_str());
    e.dur            = atoi(field[6].c_str());
    equips.push_back(e);
  }

  equip_in.close();
}
