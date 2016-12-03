#pragma once
#include <iostream>
#include <iterator>

#include "Move.h"
#include "Room.h"
#include "Stack.h"

const std::string direction_ctos(const char d)
{
  switch (d)
  {
    case 'N':
      return "North";
      break;
    case 'S':
      return "South";
      break;
    case 'E':
      return "East";
      break;
    case 'W':
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
    void back();
    void move(const char);
    void print_history();
    ~Map();
};

Map::Map()
{
  Player p = Player();
  this->head = Room(p);
  this->current = head;
}

void Map::back()
{
  if (movement_history.is_empty())
  {
    std::cout << "You cannot go back.\n";
  }
  else
  {
    switch(this->movement_history.top().reverse())
    {
      case 'N':
        this->current = this->current.north;
        break;
      case 'S':
        this->current = this->current.south;
        break;
      case 'E':
        this->current = this->current.east;
        break;
      case 'W':
        this->current = this->current.east;
        break;
      default:
        std::cout << "Something went wrong in Map::back\n";
        exit(1);
    }
    std::cout << "You went " << direction_ctos(movement_history.top().reverse()) << std::endl;
    movement_history.pop();
  }
}

void Map::move(const char d)
{
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
}

void Map::print_history()
{
  const std::vector<Move> v = this->movement_history.raw_vector();
  std::vector<Move>::const_iterator iter;
  for (iter = v.begin(); iter != v.end(); iter++)
  {
    switch ((* iter).direction())
    {
      case 'N':
      case 'S':
      case 'E':
      case 'W':
        std::cout << direction_ctos((* iter).direction()) << '\n';
        break;
      default:
        std::cout << "Something went wrong in Map::print_history\n";
        exit(1);
    }
  }
}
