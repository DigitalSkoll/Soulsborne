#include <iostream>
#include "../include/Role.h"

using namespace std;

int main()
{
  load_race();
  int id = 0;
  cout << "Race ID > ";
  cin >> id;

  cout << races[id].name << endl;
  cout << "==============" << endl;;
  cout << "HP:  " << races[id].hp << endl;
  cout << "MP:  " << races[id].mp << endl;
  cout << "ATK: " << races[id].attack << endl;

  return 0;
}
