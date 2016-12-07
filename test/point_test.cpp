#include <iostream>

using namespace std;

void hello(void (*bar))
{
  cout << "Hello";
  bar;
}

void world()
{
  cout << " World\n";
}

int main()
{
  void (*foo);

  world();

//  foo = &world;

  hello(foo);

}
