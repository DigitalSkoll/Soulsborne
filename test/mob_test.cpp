#include <iostream>
#include "../include/Mob.h"

using namespace std;

int main()
{
  load_races();
  load_paths();
  Mob m_one;

  m_one.apply_race(2);
  m_one.apply_path(3);

  cout << m_one.getRace() << endl;
  cout << m_one.getPath() << endl;

  m_one.print();

}
