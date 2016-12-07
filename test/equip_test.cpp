#include <iostream>
#include <fstream>
#include <string>
#include "../include/Role.h"

using namespace std;

int main()
{
  load_equips();
  int id;

  cout << "Equipment ID > ";
  cin >> id;

  cout << equips[id].name << endl;
  cout << "====================\n";
  cout << "ATK : " << equips[id].attack << endl;
  cout << "ARM : " << equips[id].armor << endl;
  cout << "SHI : " << equips[id].shield << endl;

  return 0;
}
