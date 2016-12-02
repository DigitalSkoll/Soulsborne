#include <iostream>
#include <string>

#include "Map.h"

int main()
{
  Map m;
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
        m.move(response);
        break;
      case 'B':
        m.back();
        break;
      case 'P':
        m.print_history();
        break;
      case 'Q':
        std::cout << "Good Bye\n";
        break;
      default:
        std::cout << "I don't know how to do that.\n";
    }
  }
  return 0;
}
