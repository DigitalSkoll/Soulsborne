#include <iostream>
#include <string>
#include <ctime>
#include "Player.h"
#include "Mob.h"

using namespace std;


int main(int argc, char *argv[])
{

  fstream file("race.csv");
  string line;
  char deli = ',';
  string value;

  getline(file, line);

  cout << line << endl;



  return 0;
}
