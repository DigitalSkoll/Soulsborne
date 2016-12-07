#include <iostream>
#include <fstream>
#include <string>
#include "../include/Role.h"

using namespace std;

int main()
{
  load_paths();
  int id;

  cout << "Path ID > ";
  cin >> id;
  if (paths.empty())
    cout << "Empty\n";

  cout << paths[id].name << endl;
  cout << "====================\n";
  cout << "HP : " << paths[id].hp << endl;
  cout << "MP : " << paths[id].mp << endl;
  cout << "ATK: " << paths[id].attack << endl;

  return 0;
}
