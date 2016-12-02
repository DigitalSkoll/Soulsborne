#include <iostream>

class Move
{
  private:
    char dir;
  public:
    Move(char d);
    char direction() const;
    char reverse() const;
};

Move::Move(char d)
{
  dir = d;
}

char Move::direction() const
{
  return dir;
}

char Move::reverse() const
{
  char reverse;
  switch (dir)
  {
    case 'N':
      reverse = 'S';
      break;
    case 'S':
      reverse = 'N';
      break;
    case 'E':
      reverse = 'W';
      break;
    case 'W':
      reverse = 'E';
      break;
    default:
      reverse = '!';
  }
  return reverse;
}
