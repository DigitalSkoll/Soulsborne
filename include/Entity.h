//==========================================
// Entity Class
//
// Base class
// Marvin S. Leister
//==========================================

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Item.h"


class Entity
{
	protected:
		std::string name; 	// Entity Name
    int speed;          // speed 
		int hp;			        // Health Points
		int mp;			        // Mana Points
		int armor;		      // reduce incoming damage to hp by this amount
		int shield;		      // takes damage before health
		int shield_armor;	  // reduce damage delt to shield
		int base_attack;	  // basic damage delt
		int wallet;		      // Money
		bool dead;		      // alive or dead
		vector<Item> list;	// Inventory
	public:
		// Constructors
		Entity();
		Entity(std::string n, int sp, int h, int m, int a, int s, int sa, int ba, int money);

    void setStats(int sp, int h, int m, int a, int s, int sa, int ba, int money);

		// Getters
		std::string get_name();
    int get_speed();
		int get_hp();
		int get_mp();
		int get_armor();
		int get_shield();
		int get_shield_armor();
		int get_base_attack();
		bool is_dead();
		int get_wallet();

		// Setters
		void set_name(std::string n);
    void set_speed(int sp);
		void set_hp(int h);
		void set_mp(int m);
		void set_armor(int a);
		void set_shield(int s);
		void set_shield_armor(int sa);
		void set_base_attack(int ba);
		void set_dead(bool d);
		void set_wallet(int m);

		int attack();					                        // Entity returns attack
		void take_damage_shield(int d); 		          // Entity Shield takes damage
		void take_damage_hp(int d);			              // Entity HP takes damage
		void print();					                        // Print info
		void add_item(Item& i);				                // Add Item to inventory
		void use_item(Item& i);				                // Apply item bonus to entity
		void print_inven(int i);			                // print iventory item at index i
		void print_inven(vector<Item>::iterator& it);	// print iventory item using iterator
		void print_all_inven();				                // print every item in inventory
		int num_inven();				                      // print number of items in inventory
		int inven_cost();				                      // print total cost of items in inventory

};


// Constructors
Entity::Entity()
{
	this->name = "[ ]";
  this->speed = 10;
	this->hp = 10;
	this->mp = 10;
	this->armor = 10;
	this->shield = 10;
	this->shield_armor = 10;
	this->base_attack = 10;
	this->dead = false;
	this->wallet = 100;
}

Entity::Entity(std::string n, int sp, int h, int m, int a, int s, int sa, int ba, int money)
{
	this->name = n;
  this->speed = sp;
	this->hp = h;
	this->mp = m;
	this->armor = a;
	this->shield = s;
	this->shield_armor = sa;
	this->base_attack = ba;
	this->dead = false;
	this->wallet = money;
}

void Entity::setStats(int sp, int h, int m, int a, int s, int sa, int ba, int money)
{
  this->speed = sp;
	this->hp = h;
	this->mp = m;
	this->armor = a;
	this->shield = s;
	this->shield_armor = sa;
	this->base_attack = ba;
	this->wallet = money;
}

// Getters
std::string Entity::get_name() { return this->name; }
int Entity::get_speed() { return this->speed; }
int Entity::get_hp() { return this->hp; }
int Entity::get_mp() { return this->mp; }
int Entity::get_shield() { return this->shield; }
int Entity::get_shield_armor() { return this->shield_armor; }
int Entity::get_base_attack() { return this->base_attack; }
bool Entity::is_dead() { return this->dead; }
int Entity::get_wallet() { return this->wallet; }

// Setters
void Entity::set_name(std::string n) { this->name = n; }
void Entity::set_speed(int sp) { this->speed = sp; }
void Entity::set_hp(int h) { this->hp = h; }
void Entity::set_mp(int m) { this->mp = m; }
void Entity::set_armor(int a) { this->armor = a; }
void Entity::set_shield(int s) { this->shield = s; }
void Entity::set_shield_armor(int sa) { this->shield_armor = sa; }
void Entity::set_base_attack(int ba) { this->base_attack = ba; }
void Entity::set_dead(bool d) { this->dead = d; }
void Entity::set_wallet(int m) { this->wallet = m; }

// attack()
// returns attack or returns 0 if the entity misses
// if the entity misses or not depends on a random number
// if the number is above 10 it is a hit
// if the number is below 10 it is a miss
int Entity::attack()
{

	int dice = rand()%20 + 1;
	if (dice >= 10)
		return this->base_attack;
	else
		return 0;
}

// take_damage_shield(int d)
// takes d as the damage delt and subtracts it from shield of the entity
// this will call take_damage_hp(int d) if shield is 0
void Entity::take_damage_shield(int d)
{
	int damage;
	if (this->shield <= 0)
		this->take_damage_hp(d);
	else
	{
		damage = d - this->shield_armor;
		if (damage < 0)
			damage = 0;
		this->shield -= damage;
		if (this->shield < 0)
		{
			damage = -1 * this->shield;
			this->shield = 0;
			this->take_damage_hp(damage);
		}

	}

}

// take_damage_hp(int d)
// takes d as the damage delt and subtracts it from health of the entity
// before return take_damage will test if player is dead or not
void Entity::take_damage_hp(int d)
{
	int damage;
	if (this->shield > 0)
		this->take_damage_shield(d);
	else
	{
		damage = d - this->armor;
		if (damage < 0)
			damage = 0;
		this->hp -= damage;
		if (this->hp <= 0)
			this->dead = true;
	}
}

// print()
// print out basic info about the entity
void Entity::print()
{
	std::cout << "Name: 		" << this->name << std::endl;
  std::cout << "Speed:          " << this->speed << std::endl;
	std::cout << "HP: 		" << this->hp << std::endl;
	std::cout << "MP: 		" << this->mp << std::endl;
	std::cout << "Wallet:		" << this->wallet << std::endl;
	std::cout << "Armor: 		" << this->armor << std::endl;
	std::cout << "Shield: 	" << this->shield << std::endl;
	std::cout << "Shield Armor: 	" << this->shield_armor << std::endl;
	std::cout << "Base Attack: 	" << this->base_attack << std::endl;
	if (is_dead())
		std::cout << "Status: 	Dead\n";
	else
		std::cout << "Status: 	Alive\n";
}

// use_item(Item& i)
// apply the bonus of the item passed in to the entity
void Entity::use_item(Item& i)
{
	this->armor += i.get_armor_bonus();
	this->base_attack += i.get_attack_bonus();
}
// add_item(Item& i)
// test if the entity has enough money to buy the item
// if entity has enough subtract cost of item from wallet
// push item to the end of the vector and use the use_item(Item& i)
// function to apply armor and attack bonus from item to entity
void Entity::add_item(Item& i)
{
	if (this->wallet < i.get_cost())
	{
		std::cout << "[ERROR] Insufficent Funds for " << i.get_name() << endl;
	}
	else 
	{
		this->wallet -= i.get_cost();
		list.push_back(i);
		this->use_item(i);
	}
}

// print_inven(int i)
// print item from inventory at index i
// use the print() function from Item object 
// to print out the item information
void Entity::print_inven(int i)
{
	this->list[i].print();
}

// print_inven(vector<Item>::iterator& it)
// same thing as print_inven(int i) except using 
// a vector iterator
void Entity::print_inven(vector<Item>::iterator& it)
{
	it->print();
}

// print_all_inven()
// print all items in inventory using an iterator
// and print_inven(vector<Item>::iterator& it)
void Entity::print_all_inven()
{
	vector<Item>::iterator it;
	for (it =this->list.begin(); it < this->list.end(); it++)
		this->print_inven(it);
	
}

int Entity::num_inven()
{
	return list.size();
}

int Entity::inven_cost()
{
	int max = 0;
	vector<Item>::iterator it;
	for (it =this->list.begin(); it < this->list.end(); it++)
		max += it->get_cost();

	return max;
	
}
