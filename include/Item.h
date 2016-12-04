//=======================================
// 		Item
// 	item header file
//
//=======================================

#pragma once
#include <iostream>
#include <string>

using namespace std;

class Item
{
	protected:
		string name;		// Name of Item
    int hp_gain;      // add to hp
    int mp_gain;      // add to mp
    int armor_gain;   // add to armor
	public:
		// Constructors
		Item(string n="[ ]",  int hp=0, int mp=0, int armor=0);

		// Getters
		string get_name();
		int get_hp_gain();
		int get_mp_gain();
		int get_armor_gain();

		// Setters
		void set_name(string n);
		void set_hp_gain(int hp);
		void set_mp_gain(int mp);
		void set_armor_gain(int a);

		void print();		// Print out basic info of Item
};

// Constructors
Item::Item(string n, int hp, int mp, int armor)
{
	this->name = n;
	this->hp_gain = hp;
	this->mp_gain = mp;
	this->armor_gain = armor;
}

// Getters
string Item::get_name()    { return this->name; }
int Item::get_hp_gain()    { return this->hp_gain; }
int Item::get_mp_gain()    { return this->mp_gain; }
int Item::get_armor_gain() { return this->armor_gain; }

// Setters
void Item::set_name (string n)   { this->name = n; }
void Item::set_hp_gain(int hp)   { this->hp_gain = hp; }
void Item::set_mp_gain(int mp)   { this->mp_gain = mp; }
void Item::set_armor_gain(int a) { this->armor_gain = a; }

// print()
// print out basic info about item in a box for style
void Item::print()
{
	cout << "+=================+\n";
	cout << "| Item  : " << this->name << endl;
	cout << "| HP+   : " << this->hp_gain << endl;
	cout << "| MP+   : +" << this->mp_gain << endl;
	cout << "| Armor+: +" << this->armor_gain << endl;
	cout << "+=================+\n";
}
