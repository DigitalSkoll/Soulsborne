#include <iostream>

enum bearing
{
  N = 0,
  S,
  E,
  W,
  FAIL = -1
};

class Move
{
  private:
    bearing dir;
  public:
    Move(bearing d);
    bearing direction() const;
    bearing reverse() const;
};

Move::Move(bearing d)
{
  dir = d;
}

bearing Move::direction() const
{
  return dir;
}

bearing Move::reverse() const
{
  bearing reverse;
  switch (dir)
  {
    case N:
      reverse = S;
      break;
    case S:
      reverse = N;
      break;
    case E:
      reverse = W;
      break;
    case W:
      reverse = E;
      break;
    default:
      reverse = FAIL;
  }
  return reverse;
}
