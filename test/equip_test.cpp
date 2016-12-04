#include <iostream>
#include "../include/Player.h"
#include "../include/Equipment.h"

using namespace std;

int main()
{
  Player p_one;
  p_one.set_name("Avem");
  p_one.apply_race(2);
  p_one.apply_path(1);

  Equipment sword("sword", 20, 0, 0, 0, 5);

  p_one.print();
  cout << endl;

  p_one.put_on('r', sword);

  p_one.print();
  cout << endl;

  p_one.print_equip();

  return 0;
}
