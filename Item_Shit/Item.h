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
		int cost;		// Cost for Item
		int armor_bonus;	// Add to armor of Entity
		int attack_bonus;	// Add to base attack of Entity
	public:
		// Constructors
		Item();
		Item(string n, int c, int armor_bonus, int attack_bonus);

		// Getters
		string get_name();
		int get_cost();
		int get_armor_bonus();
		int get_attack_bonus();

		// Setters
		void set_name(string n);
		void set_cost(int c);
		void set_armor_bonus(int b);
		void set_attack_bonus(int b);

		void print();		// Print out basic info of Item
};

// Constructors
Item::Item()
{
	this->name = "[ ]";
	this->cost = 0;
	this->armor_bonus = 0;
	this->attack_bonus = 0;
}

Item::Item(string n, int c, int armor_bonus, int attack_bonus)
{
	this->name = n;
	this->cost = c;
	this->armor_bonus = armor_bonus;
	this->attack_bonus = attack_bonus;
}

// Getters
string Item::get_name() { return this->name; }
int Item::get_cost() { return this->cost; }
int Item::get_armor_bonus() { return this->armor_bonus; }
int Item::get_attack_bonus() { return this->attack_bonus; }

// Setters
void Item::set_name (string n) { this->name = n; }
void Item::set_cost (int c) { this->cost = c; }
void Item::set_armor_bonus (int b) { this->armor_bonus = b; }
void Item::set_attack_bonus (int b) { this->attack_bonus = b; }

// print()
// print out basic info about item in a box for style
void Item::print()
{
	cout << "+=================+\n";
	cout << "| Item  : " << this->name << endl;
	cout << "| Cost  : " << this->cost << endl;
	cout << "| Armor : +" << this->armor_bonus << endl;
	cout << "| Attack: +" << this->attack_bonus << endl;
	cout << "+=================+\n";
}
