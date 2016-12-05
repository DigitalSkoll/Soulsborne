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
  Equipment shield("shield", 0, 0, 20, 5, 5);
  Equipment leather("leather", 0, 20, 0, 5);

  p_one.add_gear(sword);
  p_one.add_gear(shield);
  p_one.add_gear(leather);

  p_one.print_all_gear();

  int ans;
  cout << "Remove Gear: ";
  cin >> ans;

  p_one.remove_gear(ans);
  p_one.print_all_gear();

  cout << "Remove Gear: ";
  cin >> ans;

  p_one.remove_gear(ans);
  p_one.print_all_gear();

  return 0;
}
