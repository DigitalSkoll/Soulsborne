#pragma once
#include <iostream>
#include <iterator>

#include "Move.h"
#include "Player.h"
#include "Room.h"
#include "Stack.h"

const std::string direction_ctos(const bearing d)
{
  switch (d)
  {
    case N:
      return "North";
      break;
    case S:
      return "South";
      break;
    case E:
      return "East";
      break;
    case W:
      return "West";
      break;
    default:
      return "";
  }
}

class Map
{
  private:
    Stack<Move> movement_history;
    Player * player;
    Room * head;
    Room * current;
  public:
    Map(Player * p);
    Room * get_current() const;
    Room * get_head() const;
    void back();
    void move(const bearing);
    void print_history();
    void reset();
    void respawn();
    void scan_doors();
    ~Map();
};

Map::Map(Player * p)
{
  this->player          = p;
  this->head            = new Room(SPAWN);
  this->current         = this->head;
  this->head->previous  = this->head;
  this->head->next      = NULL;
}

Room * Map::get_current() const
{
  return this->current;
}

Room * Map::get_head() const
{
  return this->head;
}

void Map::back()
{
  if (movement_history.is_empty())
  {
    std::cout << "You cannot go back.\n";
  }
  else
  {
    bearing d = this->movement_history.top().reverse();

    switch(d)
    {
      case N:
      case S:
      case E:
      case W:
        // intentional drop through
        this->current = this->current->doors[d];
        break;
      default:
        std::cout << "Something went wrong in Map::back\n";
        exit(1);
    }

    std::cout << "You went " << direction_ctos(d) << std::endl;

    movement_history.pop();
  }
}

void Map::move(const bearing d)
{
  if (!this->movement_history.is_empty())
  {
    if (this->movement_history.top().reverse() == d)
    {
      this->back();
    }
    else
    {
      MV:
      this->movement_history.push(Move(d));

      if (this->current->doors[d] == NULL)
      {
        // create new room at door d
        this->current->doors[d]                         = new Room(NORMAL);
        // point new room prev to old last node
        this->current->doors[d]->previous               = this->head->previous;
        // link new room door reverse d to current
        this->current->doors[d]->
          doors[this->movement_history.top().reverse()] = this->current;
        // point old last node next to new last node
        this->head->previous->next                      = this->current->doors[d];
        // point  new room next to null
        this->current->doors[d]->next                   = NULL;
      }
      // set current to room at door d
      this->current = this->current->doors[d];

      std::cout << "You went " << direction_ctos(d) << std::endl;
    }
  }
  else
  {
    // I don't like using goto in this, but it's the easiest thing in this case
    // and it's not that bad here tbh
    goto MV;
  }
}

void Map::print_history()
{
  if (this->movement_history.is_empty())
  {
    std::cout << "There is no history.\n";
  }
  else
  {
    const std::vector<Move> v = this->movement_history.raw_vector();
    std::vector<Move>::const_iterator iter;
    for (iter = v.begin(); iter != v.end(); iter++)
    {
      switch ((* iter).direction())
      {
        case N:
        case S:
        case E:
        case W:
          // intentional drop through
          std::cout << direction_ctos((* iter).direction()) << '\n';
          break;
        default:
          std::cout << "Something went wrong in Map::print_history\n";
          exit(1);
      }
    }
  }
}

void Map::reset()
{
  Room * prev;
  this->current = this->head->next;

  while (this->current->next != NULL)
  {
    prev          = this->current;
    this->current = this->current->next;
    delete prev;
  }

  this->respawn();

  for (size_t i = 0; i < 4; i++)
  {
    this->current->doors[i] = NULL;
  }
}

void Map::respawn()
{
  while (!this->movement_history.is_empty())
  {
    this->movement_history.pop();
  }

  this->current = this->head;

  player->refresh();
}

void Map::scan_doors()
{
  std::cout << "Room type: ";

  switch (this->current->type)
  {
    case NORMAL:
      std::cout << "Normal\n";
      break;
    case SPAWN:
      std::cout << "Spawn\n";
      break;
    case BOSS:
      std::cout << "Boss\n";
      break;
    default:
      std::cout << "Something went terribly wrong in Map::scan_doors()\n";
  }

  for (size_t i = 0; i < 4; i++)
  {
    switch (i)
    {
      case N:
        std::cout << "North ";
        break;
      case S:
        std::cout << "South ";
        break;
      case E:
        std::cout << "East ";
        break;
      case W:
        std::cout << "West ";
        break;
      default:
        std::cout << "Something went wring in Map::scam_doors.\n";
    }

    std::cout << "door: ";

    if (this->current->doors[i] == NULL)
    {
      std::cout << "CLOSED\n";
    }
    else
    {
      std::cout << "OPEN\n";
    }
  }
}

Map::~Map()
{
  Room * prev;
  this->current = this->head;

  while (this->current->next != NULL)
  {
    prev          = this->current;
    this->current = this->current->next;
    delete prev;
  }
}
