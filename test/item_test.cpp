#include <iostream>
#include <fstream>
#include <string>
#include "../include/Role.h"

using namespace std;

int main()
{
  load_items();
  int id;

  cout << "Item ID > ";
  cin >> id;

  cout << items[id].name << endl;
  cout << "====================\n";
  cout << "HP : " << items[id].hp << endl;
  cout << "MP : " << items[id].mp << endl;
  cout << "SHI: " << items[id].shield << endl;

  return 0;
}
