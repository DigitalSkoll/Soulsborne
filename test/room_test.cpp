#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Player.h"
#include "../include/Room.h"
#include "../include/Mob.h"
#include "../include/Item.h"

using namespace std;

int main()
{
  srand(time(NULL));
  Room room;
  Player p_one;
  p_one.apply_race(2);
  p_one.apply_path(1);

  room.display_mobs();

  cout << "Battle Time\n";
  

  return 0;
}
