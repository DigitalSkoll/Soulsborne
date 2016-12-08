#include <ctime>
#include <iostream>
#include <string>

#include "Map.h"

bearing ctob(const char d);

int main()
{
  srand(time(NULL));

  load_races();
  load_paths();
  load_items();
  load_equips();

  Player * p = new Player();
  Map m(p);
  char response;
  while (response != 'Q')
  {
    std::cin >> response;

    switch (response)
    {
      case 'N':
      case 'S':
      case 'E':
      case 'W':
        // intentional drop through
        m.move(ctob(response));
        break;
      case 'B':
        m.back();
        break;
      case 'P':
        m.print_history();
        break;
      case 'T':
        m.reset();
        break;
      case 'R':
        m.respawn();
        break;
      case 'L':
        m.scan_doors();
        break;
      case 'Q':
        std::cout << "Good Bye\n";
        break;
      default:
        std::cout << "I don't know how to do that.\n";
    }
  }
  delete p;
  return 0;
}

bearing ctob(const char d)
{
  bearing ret;
  switch(d)
  {
    case 'N':
      ret = N;
      break;
    case 'S':
      ret = S;
      break;
    case 'E':
      ret = E;
      break;
    case 'W':
      ret = W;
      break;
    default:
      ret = FAIL;
  }
  return ret;
}
