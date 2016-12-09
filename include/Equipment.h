#pragma once
#include <string>
#include "Role.h"

using namespace std;

class Equipment
{
  private:
    string name;
    int attack_bonus;
    int armor_bonus;
    int shield_bonus;
    int shield_armor_bonus;
    int dur;
  public:
    Equipment(string n = "[ ]", int att = 0, int arm = 0, int shi = 0, int sab = 0, int dur = 0);

    void set_name(string n);
    void set_attack_bonus(int ab);
    void set_armor_bonus(int ab);
    void set_shield_bonus(int sb);
    void set_shield_armor_bonus(int sab);
    void set_dur(int dur);

    string get_name();
    int get_attack_bonus();
    int get_armor_bonus();
    int get_shield_bonus();
    int get_shield_armor_bonus();
    int get_dur();

    void print();
    void print_name();
    void operator=(const Equipment &other);
    void gen_gear();
};

Equipment::Equipment(string n, int att, int arm, int shi, int sab, int dur)
{
  this->name = n;
  this->attack_bonus = att;
  this->armor_bonus = arm;
  this->shield_bonus = shi;
  this->shield_armor_bonus = sab;
  this->dur = dur;
}

void Equipment::set_name(string n) { this->name = n; }
void Equipment::set_attack_bonus(int att) { this->attack_bonus = att; }
void Equipment::set_armor_bonus(int  arm) { this->armor_bonus = arm; }
void Equipment::set_shield_bonus(int shi) { this->shield_bonus = shi; }
void Equipment::set_shield_armor_bonus(int sab) { this->shield_armor_bonus = sab; }
void Equipment::set_dur(int dur) { this->dur = dur; }

string Equipment::get_name() { return this->name; }
int Equipment::get_attack_bonus() { return this->attack_bonus; }
int Equipment::get_armor_bonus() { return this->armor_bonus; }
int Equipment::get_shield_bonus() { return this->shield_bonus; }
int Equipment::get_shield_armor_bonus() { return this->shield_armor_bonus; }
int Equipment::get_dur() { return this->dur; }


void Equipment::operator=(const Equipment &other)
{
  this->name = other.name;
  this->attack_bonus = other.attack_bonus;
  this->shield_bonus = other.shield_bonus;
  this->shield_armor_bonus = other.shield_armor_bonus;
  this->dur = other.dur;
}

void Equipment::print()
{
  cout << this->name << endl;
  cout << "attack bonus: " << this->attack_bonus << endl;
  cout << "shield bonus: " << this->shield_bonus << endl;
  cout << "shield armor bonus:" << this->shield_armor_bonus << endl;
  cout << "durability: " << this->dur << endl;
}

void Equipment::print_name()
{
  cout << this->name << endl;
}

void Equipment::gen_gear()
{
  int id = (rand() % equips.size());

  this->name = equips[id].name;
  this->attack_bonus = equips[id].attack;
  this->shield_bonus = equips[id].shield;
  this->shield_armor_bonus = equips[id].shield_armor;
  this->dur = equips[id].dur;
}
