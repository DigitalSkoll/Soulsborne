#pragma once
#include <iostream>
#include <iterator>

#include "Move.h"
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
    Room * head;
    Room * current;
  public:
    Map();
    Room * get_current() const;
    Room * get_head() const;
    void back();
    void move(const bearing);
    void print_history();
    ~Map();
};

Map::Map()
{
  this->head            = new Room();
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
      mv:
      this->movement_history.push(Move(d));
      if (this->current->doors[d] == NULL)
      {
        // create new room at door d
        this->current->doors[d] = new Room();
        // point new room prev to old last node
        this->current->doors[d]->previous = this->head->previous;
        // link new room door reverse d to current
        this->current->doors[d]->doors[this->movement_history.top().reverse()] = this->current;
        // point old last node next to new last node
        this->head->previous->next    = this->current->doors[d];
        // point  new room next to null
        this->current->doors[d]->next = NULL;
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
    goto mv;
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
          std::cout << direction_ctos((* iter).direction()) << '\n';
          break;
        default:
          std::cout << "Something went wrong in Map::print_history\n";
          exit(1);
      }
    }
  }
}

Map::~Map()
{
  Room * prev;
  this->current = this->head;
  while (this->current->next != NULL)
  {
    prev = this->current->previous;
    this->current = this->current->next;
    delete prev;
  }
}
