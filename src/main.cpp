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

  std::string name;
  std::cout << "Enter a name: ";
  getline(std::cin, name);
  std::cout << '\n';
  Player * p = new Player(
      name, "Human", "Warrior",
      2, 50, 20, 1, 0, 0, 10, 0);
  Map m(p);
  std::string response;

  std::cout << "Type \"help\" for commands\n";

  while (true)
  {
    std::cout << " ~> ";

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
    else if ("doors" == response)
    {
      m.scan_doors();
    }
    else if ("mobs" == response)
    {
      m.get_current()->display_mobs();
    }
    else if ("stats" == response)
    {
      p->print();
    }
    else if ("inve" == response)
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
                << "doors - show the doors\n"
                << "mobs - show mobs\n"
                << "stats - show your stats\n"
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
