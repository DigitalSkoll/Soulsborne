#include <iostream>
#include <fstream>
#include <string>
#include "../include/Role.h"

using namespace std;

int main()
{
  load_races();
  int id;

  cout << "RACE ID > ";
  cin >> id;

  cout << races[id].name << endl;
  cout << "====================\n";
  cout << "HP : " << races[id].hp << endl;
  cout << "MP : " << races[id].mp << endl;
  cout << "ATK: " << races[id].attack << endl;

  return 0;
}
