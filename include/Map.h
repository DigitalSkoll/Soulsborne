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
    Map(Player p);
    Room * get_current() const;
    Room * get_head() const;
    void back();
    void move(const bearing);
    void print_history();
    ~Map();
};

Map::Map(Player p)
{
  this->head = new Room(p);
  this->current = this->head;
  this->head->previous = this->head;
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
  if (!this->movement_history.is_empty() && this->movement_history.top().reverse() == d)
  {
    this->back();
  }
  else
  {
    if (this->current->doors[d] == NULL)
    {
      this->current->doors[d] = new Room();
      this->head->previous->next = this->current;
      this->head->previous = this->current;
    }
    this->current = this->current->doors[d];
    this->movement_history.push(Move(d));
    std::cout << "You went " << direction_ctos(d) << std::endl;
  }
  /*
  if (!movement_history.is_empty())
  {
    if (movement_history.top().reverse() == d)
    {
      this->back();
    }
    else
    {
      movement_history.push(Move(d));
      std::cout << "You went " << direction_ctos(d) << std::endl;
    }
  }
  else
  {
    movement_history.push(Move(d));
    std::cout << "You went " << direction_ctos(d) << std::endl;
  }
  */
}

void Map::print_history()
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

Map::~Map()
{
  Room * prev;
  this->current = this->head;
  while (this->current != NULL)
  {
    prev = this->current->previous;
    this->current = this->current->next;
    delete prev;
  }
}
