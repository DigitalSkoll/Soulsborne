#include <iostream>
#include "../include/Player.h"

using namespace std;

int main()
{
  load_races();
  load_paths();
  Player p_one("Avem");


  p_one.apply_race(2);
  p_one.apply_path(1);

  cout << p_one.get_name() << endl;
  cout << p_one.getRace() << endl;
  cout << p_one.getPath() << endl;

  p_one.inven_mgmt();

}
