#include <iostream>
#include "../include/Item.h"
#include "../include/Player.h"

using namespace std;

int main()
{
  Item health("health potion", 99, 0 ,0);
  Item mana("mana potion", 0, 99, 0);
  Item repair("repair powder", 0, 0, 99);
  Player p_one("Avem");
  p_one.apply_race(6);
  p_one.apply_path(1);

  p_one.print();
  cout << endl;

  p_one.set_hp(1);
  p_one.set_mp(1);
  p_one.set_shield(1);

  p_one.print();
  cout << endl;

  p_one.add_item(health);
  p_one.add_item(mana);
  p_one.add_item(repair);
  p_one.print_all_inven();
  cout << endl;
  p_one.use_item(1);
  p_one.use_item(1);
  p_one.use_item(1);

  p_one.print();

  p_one.print_all_inven();
  cout << endl;

}
