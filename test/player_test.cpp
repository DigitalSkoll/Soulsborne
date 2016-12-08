#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Player.h"

using namespace std;

int main()
{
  srand(time(NULL));
  load_races();
  load_paths();
  load_items();
  load_equips();
  Player p_one("Avem");


  p_one.apply_race(2);
  p_one.apply_path(1);

  cout << p_one.get_name() << endl;
  cout << p_one.getRace() << endl;
  cout << p_one.getPath() << endl;

  Equipment e;
  e.gen_gear();

  p_one.add_gear(e);

  e.gen_gear();

  p_one.add_gear(e);


  p_one.gear_mgmt();

}
