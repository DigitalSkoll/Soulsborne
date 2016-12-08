#include <cstring>
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
  std::string response;

  std::cout << "Type \"help\" for commands\n";

  while (true)
  {
    getline(std::cin, response);

    if ("north" == response ||
        "south" == response ||
        "east" == response ||
        "west" == response)
    {
      m.move(ctob(toupper(response.at(0))));
    }
    else if ("back" == response)
    {
      m.back();
    }
    else if ("history" == response)
    {
      m.print_history();
    }
    else if ("scan" == response)
    {
      m.scan_doors();
    }
    else if ("mobs" == response)
    {
      m.get_current()->display_mobs();
    }
    else if ("inventory" == response)
    {
      p->inven_mgmt();
    }
    else if ("gear" == response)
    {
      p->gear_mgmt();
    }
    else if ("help" == response)
    {
      std::cout << "[north | south | east | west] - go [north | south | east | west]\n"
                << "back - go back (removes last move from history)\n"
                << "history - show your movement history\n"
                << "mobs - show mobs\n"
                << "inve - start inventory mgmt\n"
                << "gear - start gear mgmt\n"
                << "quit - quit the game\n"
                << "help - print this message\n";
    }
    else if ("quit" == response)
    {
      std::cout << "Good Bye\n";
      break;
    }
    else
    {
      std::cout << "I don't know how to \"" << response << "\"" << std::endl;
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
